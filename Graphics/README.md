# Graphics

## Gaussian Splatting

Gaussian splatting is a groundbreaking volume rendering technique that has rapidly gained popularity for its ability to produce high-quality, real-time renderings of 3D scenes. This method represents a significant advancement in computer graphics, offering a novel way to synthesize new views of a scene from a collection of images or videos. Unlike traditional methods that rely on polygonal meshes or the computationally intensive neural networks of Neural Radiance Fields (NeRFs), Gaussian splatting represents scenes with a multitude of 3D Gaussian primitives. This approach not only allows for photorealistic rendering at high resolutions but also significantly accelerates both training and rendering times.

The core idea behind Gaussian splatting is to represent a 3D scene as a collection of "splats," where each splat is a Gaussian function with specific properties. These Gaussians are then projected onto a 2D image plane and blended together to create the final image. The technique was first introduced in the early 1990s but was revitalized in 2023 with the proposal of 3D Gaussian splatting for real-time radiance field rendering.

The initial step in creating a Gaussian splatting model involves using the Structure from Motion (SfM) method to generate a sparse point cloud from a set of input images. Each point in this cloud is then converted into a 3D Gaussian. Through an optimization process that minimizes the difference between the rendered images and the original training images, these Gaussians are refined to accurately represent the scene's geometry and appearance.

### Key Parameters of Gaussian Splatting

Each 3D Gaussian in the scene is defined by a set of key parameters that are optimized during the training process. These parameters dictate the position, shape, color, and transparency of each individual "splat":

* **Position (Mean):** This 3D coordinate (x, y, z) defines the center of the Gaussian in 3D space.
* **Covariance Matrix:** This 3x3 matrix determines the shape, size, and orientation of the Gaussian ellipsoid. It can be decomposed into a scaling matrix (for size) and a rotation matrix (for orientation). This allows for anisotropic Gaussians that can represent elongated or flattened shapes, crucial for accurately modeling complex geometries.
* **Color:** The color of the Gaussian is typically represented using spherical harmonics. This allows for view-dependent effects, meaning the color can change depending on the viewing direction, which is essential for capturing realistic lighting and reflections.
* **Opacity (Alpha):** This value, typically between 0 and 1, controls the transparency of the Gaussian. Opacity is crucial for rendering scenes with both solid and translucent objects, as well as for the blending process during rendering.

### Efficiently Rendering Gaussian Splatting

One of the most significant advantages of Gaussian splatting is its rendering efficiency, which enables real-time performance even at high resolutions. This is achieved through a specialized tile-based rasterization pipeline that is highly parallelizable on modern GPUs.

The key steps for efficient rendering include:

1. **View Frustum Culling:** Initially, any Gaussians that are outside the camera's view are discarded to avoid unnecessary computations.
2. **Projection to 2D:** The remaining 3D Gaussians are projected onto the 2D screen space. This transforms the 3D ellipsoids into 2D splats.
3. **Tile-Based Rasterization:** The screen is divided into small, fixed-size tiles (e.g., 16x16 pixels). Each Gaussian is then assigned to the tiles it overlaps with. This allows for processing multiple tiles in parallel.
4. **Sorting:** Within each tile, the Gaussians are sorted by their depth. This is a crucial step for correct alpha blending, ensuring that objects closer to the camera correctly obscure those farther away. Fast GPU sorting algorithms are employed to make this process highly efficient.
5. **Alpha Blending:** For each pixel within a tile, the colors of the sorted Gaussians that cover that pixel are blended together in a front-to-back order, taking their opacity into account.

To further enhance rendering speed, several optimization strategies are employed:

* **Pre-processing:** Some calculations, like determining the 2D radius and color from spherical harmonics, are done in a pre-processing step.
* **Efficient Data Structures:** Using efficient data structures, such as storing depth and tile ID in a single 64-bit value, accelerates the sorting process.
* **Redundancy Elimination:** Advanced techniques aim to eliminate redundant computations, such as accurately identifying which tiles a Gaussian will intersect without unnecessary checks.
* **Adaptive Workload Partitioning:** Dynamically adjusting how rendering tasks are divided based on the size and complexity of the Gaussians can further optimize performance.

These sophisticated rendering techniques, combined with the explicit and flexible nature of the 3D Gaussian representation, are what allow Gaussian splatting to achieve state-of-the-art visual quality at real-time frame rates.
