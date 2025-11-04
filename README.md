# Raytracer

![Main Image](example_img.png)

## Features

* Anti-aliasing
* Shapes
  * Spheres
  * Cubes
* Materials
  * Diffuse/Lambertian
  * Metal (with fuzziness)
  * Dielectrics
* Defocus Blur
* Camera Positioning
* Bounding Volume Hierarchies for Axis-Aligned Bounding Boxes
* Multithreading

## Performance Optimisation Benchmark

#### Rendering Configuration
* 1200x675 Resolution
* 50 Antialiasing Samples
* 50 Maximum Ray Bounces
* Complex Scene is 488 Objects
* Simple Scene is 40 Objects

#### Table 1 — Performance Benchmarks for Optimisation Methods
| Optimisation                      | Scene   | Render Time (s) |
| --------------------------------- | ------- | --------------: |
| None                              | Simple  |         205.159 |
| Bounding Volume Hierarchies (BVH) | Simple  |         158.729 |
| Multithreading                    | Simple  |          22.719 |
| Multithreading + BVH              | Simple  |          19.078 |
| None                              | Complex |        2302.441 |
| BVH                               | Complex |         411.613 |
| Multithreading                    | Complex |         218.560 |
| Multithreading + BVH              | Complex |          38.271 |

#### Table 2 — Thread Scaling Benchmark for Complex Scenes (with BVH)
| Thread Count | Render Time (s) |
| ------------ | --------------- |
| 1            | 411.613         |
| 2            | 213.390         |
| 4            | 110.742         |
| 8            | 59.991          |
