#!/bin/bash

# This script examines all .webm, .mkv, and .mp4 files in the current directory.
# If a file does not have a corresponding .mpg file with the same base name,
# it converts the source file to .mpg using ffmpeg.

echo "Starting video to MPG conversion check..."
echo "-----------------------------------------"

converted_count=0

# Loop through all specified video files in the current directory
for source_file in *.webm *.mkv *.mp4; do
    # If no files match the pattern, the loop runs once with the literal string.
    # This check ensures we only process actual files.
    if [ ! -f "$source_file" ]; then
        continue
    fi

    # Extract the base name of the file (e.g., "video" from "video.mkv")
    base_name="${source_file%.*}"

    # Construct the target .mpg file name
    mpg_file="${base_name}.mpg"

    echo "Checking: $source_file"

    # Check if the corresponding .mpg file already exists
    if [ ! -f "$mpg_file" ]; then
        echo "  -> No corresponding '$mpg_file' found. Converting..."

        # Use ffmpeg to convert the source file to .mpg
        # -i: specifies the input file
        # -q:v 0: sets video quality to highest. Use a higher value (e.g., 2-5) for smaller files.
        # -loglevel error: suppresses all ffmpeg output except for errors.
        ffmpeg -i "$source_file" -q:v 0 "$mpg_file" -loglevel error

        # Check the exit status of ffmpeg
        if [ $? -eq 0 ]; then
            echo "  ✅ Successfully converted '$source_file' to '$mpg_file'."
            ((converted_count++))
        else
            echo "  ❌ Error: Failed to convert '$source_file'."
        fi
    else
        echo "  -> '$mpg_file' already exists. Skipping."
    fi
    echo "-----------------------------------------"
done

echo "Conversion check complete. Total files converted: $converted_count"
