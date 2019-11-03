# The best interactive tutorial: [https://www.codecademy.com/learn/learn-git Codecademy Git]
# https://try.github.io
# Book: [https://github.s3.amazonaws.com/media/progit.en.pdf Pro Git], [http://hoth.entp.com/output/git_for_designers.html Git for designers], [http://toroid.org/git-website-howto Using Git to manage a web site]
# Hosting: [https://bitbucket.org/ Bitbucket], [https://github.com/ Github]


# Generate a new SSH Key
#   1. Open Git bash
#   2. ssh-keygen -t rsa -b 4096 -C "x@y.z"
#   3. Enter

# Setup username and email
#  git config user.name "Billy Everyteen"
# Set a new name
    git config user.name
# Verify the setting
    git config --global user.name "Ruofei Du"
    git config --global user.email "x@y.z"

# Restore a file
    git checkout HEAD file.txt
# Restore a file from master
    git checkout origin/master filename
# Revert to previous commit
    git log
    git reset --hard <SOME-COMMIT>
# Unstage a file
    git reset HEAD file.txt
# Change the HEAD cursor
    git reset SHA(first 7 letters of a commit in git log)
# Initialize a new branch
    git branch new_branch
    git checkout new_branch
    git add file.txt
    git commit -m "add new file file.txt"
    git checkout master
    git merge new_branch
    git commit -m "conflict resolved"
    git branch -d new_branch
# Push an existing folder to remote git repo:
## remember to add .gitignore first, otherwise all files will be versioned.
    cd existing_folder
    git init
    git remote add origin git@gitlab.umiacs.umd.edu:username/your-repo-name.git
    git add .
    git commit -m "Initial commit"
    git push -u origin master

# Switch to an existing branch
    git branch master
    git checkout master
# List remotes
    git remote -v
# Update changes that others made into origin/master, then merge to copy master
    git fetch
    git merge origin/master
# Push commits
    git push origin new_branch
# Force update
    git checkout master
    git branch new-branch-to-save-current-commits
    git fetch --all
    git reset --hard origin/master
# List all branches
    git remote show origin
# Rename branch
    git branch -m new-name // If you are on the branch you want to rename
    git branch -m old-name new-name // If you are on a different branch
    git push origin :old-name new-name // Delete the old-name remote branch and push the new-name local branch. Reset the upstream branch for the new-name local branch.
    git push origin -u new-name // Switch to the branch and then:
# Keep forked repo up-to-date
    git remote add upstream https://github.com/[Original Owner Username]/[Original Repository].git
    git fetch upstream
    git checkout master
    git merge upstream/master
    git push
# Add submodule
	git submodule add https://github.com/ruofeidu/DuEngine

# Other commands
    git init
    git status
    git add '*.txt'
    git commit -m 'add x'
    git log
    git remote add origin https://github.com/try-git/try_git.git
    git push -u origin master
    git pull origin master
    git diff HEAD
    git diff --staged
