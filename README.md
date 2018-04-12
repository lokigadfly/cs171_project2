# Introduction

In the last assignment, you have been familiar with the basic graphics programs with OpenGL, where you should have been able to render simple geometric objects. In this assignment, we go further based on assignment 1 that we construct more complex geometric objects, basically with Bézier surfaces. The rendering of the geometries is the same as in assignment 1 where you can choose to either shade the objects with OpenGL fixed pipeline (Gourand shading) or implement per-pixel Phong shading in shaders as the optional work in assignment 1 to give better visual results. What you really need to do in this assignment is how the complex geometries could be constructed by yourself and how to texture them. You will be required to implement the Bézier surface construction method with a particular triangulation algorithm to draw complex shapes. In addition, you need to texture the Bézier surface using OpenGL texture mapping techniques.

# Things to be done

- [must] Based on assignment 1, construct triangle meshes based on Bézier surfaces, where several control points should be first specified to form a control mesh (at least 5x5 control mesh).
- [must] Render the constructed surface with lighting (Gourand or Phong shading), and texture the surface with a provided or your own generated image.
- [must] Use keyboard or mouse to view the surfaces at different positions.
- [optional] You can use mouse to select the control points and edit their positions; you can also patch together multiple Bézier surfaces to form complex objects.
- [optional] You can also implement adaptive triangulation method to give denser triangles in regions with steeper shape changes.