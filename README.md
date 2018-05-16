Assignment 2 - Geometric Modeling

---

Introduction

In the last assignment, you have been familiar with the basic graphics programs with OpenGL, where you should have been able to render simple geometric objects. In this assignment, we go further based on assignment 1 that we construct more complex geometric objects, basically with Bézier surfaces. The rendering of the geometries is the same as in assignment 1 where you can choose to either shade the objects with OpenGL fixed pipeline (Gourand shading) or implement per-pixel Phong shading in shaders as the optional work in assignment 1 to give better visual results. What you really need to do in this assignment is how the complex geometries could be constructed by yourself and how to texture them. You will be required to implement the Bézier surface construction method with a particular triangulation algorithm to draw complex shapes. In addition, you need to texture the Bézier surface using OpenGL texture mapping techniques.

---

Things to be done

- [must] Based on assignment 1, construct triangle meshes based on Bézier surfaces, where several control points should be first specified to form a control mesh (at least 5x5 control mesh).

- [must] Render the constructed surface with lighting (Gourand or Phong shading), and texture the surface with a provided or your own generated image.

- [must] Use keyboard or mouse to view the surfaces at different positions.

- [optional] You can use mouse to select the control points and edit their positions; you can also patch together multiple Bézier surfaces to form complex objects.

- [optional] You can also implement adaptive triangulation method to give denser triangles in regions with steeper shape changes.

---

Submission & demonstration

Code submission deadline: 2018-4-13, 23:59pm

Demonstration date & time: 2018-4-16, 7pm-9pm

Please send your code package and technical report to TAs though email (check who you should send your assignment to on Piazza)

---

Grading rules

- The [must] items are things that you must finish. When you have finished all the [must] items and demonstrate them successfully in front of TAs, you will get all the scores for the programming part. [90%]

- In addition to programming, you will also need to submit a technical report specifying the details of your implementation: what you have done and how you achieve them. [10%]

- You can also choose to do optional items, and if you choose to do any of them, you will get additional scores based on the additional work you have done. But the maximum additional score will not exceed 20% of the entire score of this assignment. 

- Late submission of your assignment will subject to score deduction. Please refer to Late hand-in policy for details.

---

Note:Before doing the assignment, please read the materials on curve and surface modeling, and in particular, Bézier curves and surfaces. You can also refer to Delaunay triangulation and subdivision methods for more advanced implementations.

---

Before you start doing your assignment, you first need to know more in detail about how geometries are constructed with Bézier curves and surfaces, and how meshes are constructed by triangulation. In the following, we will introduce the related concepts and procedures in order to help you finish this assignment.Bézier curve constructionThe basic method for constructing free-form surfaces in order to represent complex geometrical objects is to employ the parametric form with polynomials. The Bézier curve is the one of the parametric representations of a curve by Bernstein polynomials,  which is formulated as:                  where t is the parameter in the range [0,1]; Pi (i=0,1,...,n) are the control points used to construct the curve (Pi=[xi,yi,zi] in 3D); n is the degree of the curve, which is connected to the number of control points (n=number of control points - 1). To evaluate a particular point on the curve, we give a specific value of t, and the above formula gives the coordinate [x(t), y(t), z(t)] of the curve. Evaluating such a formula is expensive in computation since it involves a number of multiplications, which are slow. The efficient implementation of Bézier curve evaluation is the well-known de Casteljau's algorithm, which is briefly described here, where recursive definition is used as follows:                   Taking Figure 1 as an example, where a quadratic Bézier curve is constructed (n=2) with 3 control points P0, P1 and P2. To evaluate a point B on the curve where t=0.25, we first perform linear interpolation between point P0 and P1 to give point Q0 as Q0=(1-t)P0+tP1. Similarly, we can interpolate Q1 as Q1=(1-t)P1+tP2. Then we perform such a process recursively to obtain Q=(1-t)Q0+tQ1. Now there is only one point left and such a point is on the Bézier curve. Note some properties for Bézier curve construction that the first and last control points are exactly on the curve, and the tangent vector of a point B is formed by the last two points  Q0 and Q1 in the recursion, which is useful in calculation surface normal in Bézier surface evaluation. Also note that the edges of the control polygon connecting the first and the last points are tangential to the curve, which is important for us to construct continuous curves by patching together multiple Bézier curves.                           Figure 1

Bézier surface construction

The Bézier surface construction is based on the tensor product of the Bézier curve, which is formulated as:                    

Rearranging the formula, we can obtain:                    It is clear that the Bézier surface point evaluation can be decomposed into point evaluations of two Bézier curves.                        Figure 2Take Figure 2 for example. Specifically, we need to treat each row of the 4x4 control mesh (formed by the control points) as individual Bézier curves along either u or v directions. For the control points, we will first associate them with a (ui,vj) value in parameter space (usually, we subdivide the parameter space uniformly and associate the (ui,vi) values for the control points). Then, we first fix a vj value and use different ui values, which form the control points for the Bézier curve along u direction, where we can evaluate any point based on (u,vj). Then, we vary different vj given a fixed u value, and we get another set of control points for Bézier curve along v direction, and then we can obtain the final point with parameter (u,v). Once we know how to compute a particular point on the Bézier surface given the parameter (u,v), we can generate a mesh by sampling quadrilaterals or triangles in parameter space and then evaluate the corresponding vertices to form the final Bézier surface.Normal evaluation and lighting calculationNow we have known how to create a Bézier surface, then we need to know how to shade it. The basic shading involves lighting calculation, where you need to compute the normal at each vertex of the Bézier surface given a parameter (u,v), and such a normal can be computed accurately.From previous description, you have known that we recast the Bézier surface evaluation into two Bézier curve evaluations, and the evaluation on the last Bézier curve can give a tangent vector on the tangent plane of a particular point on the Bézier surface. Suppose we first start from Bézier curve evaluation along u direction, the final tangent vector is along v direction, as indicated by the green arrow in Figure 3. This only defines one tangent vector on the tangent plane. To determine the tangent plane we need another tangent vector, which can be calculated by starting from Bézier curve evaluation again but along v direction instead. The final tangent vector is along u direction, and we obtain another tangent vector on the tangent plane as indicated by the red arrow in Figure 3. The normal is the cross product of them. Remember that we need to normalize the normal before using it for lighting calculations.

　                      Figure 3Once we have determined the normal at any point, we can use lighting which you have done in assignment 1 to shade the surface and make it stereoscopic.Basic triangulationThe triangulation of a Bézier surface is simple. First, you can uniformly subdivide the parameter space (u,v) into M and N samples respectively, and we use (ui,vj) to indicate one of such samples. Then, the four samples P0(ui,vj), P1(ui+1,vj), P2(ui+1,vj+1), P3(ui,vj+1) form a quadrilateral in space, as shown in Figure 5.                           Figure 5To do triangulation, we further subdivide the quadrilateral P0P1P2P3 into two triangles P0P1P2 and P0P2P3, or P0P1P3 and P1P2P3. Which subdivision should be selected is based on the Delaunay property, and we select the subdivision which satisfy the Delaunay property (see the course notes as well as Delaunay triangulation). Basically, we can use the circumcircle to determine the way for subdivision.Generating texture coordinates and mapping texturesThere are many ways to do parameterization and mapping a texture onto the Bézier surface. Here we only introduce the basic method, and you are encouraged to try different kinds of parameterizations. As you have learned from the course, the texture mapping requires specifying a texture coordinate (s,t) in texture space for each vertex, which is evaluated by giving two surface parameters (u,v), as shown in Figure 2. In this case, it is very easy to assign the texture coordinate since both (s,t) and (u,v) are normalized in the space [0,1] x [0,1]. Thus, the simplest way is to let texture coordinate (s,t) equals the surface parameter (u,v), and then each vertex can be associated with such a texture coordinate.After defining the texture coordinate, you can perform texture mapping with OpenGL. First you will need to load a texture image, where we have provided you with the image loading code in the skeleton code which is shown bellow:```	int width, height, nrChannels;

	unsigned char *data = stbi_load(FileSystem::getPath("resource/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);

	//bind it to texture

	stbi_image_free(data);

`You can also generate the texture image by your own code procedures; for example, you can generate a checkerboard texture by your own code on the fly. Then you can enable texture mapping, initialize some settings and specify texture coordinate for each vertex in the mesh. Please refer to the page here for texture mapping in OpenGL.The sample code for texture mapping initialization in OpenGL is as follows:```void init(Gluint &texture_id)

{

	// acquire load our texture into an array

	// the function we use this semester is in imageio.hpp

	unsigned char* data; // TODO: give me some values!

	// enable textures

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	// sample: specify texture parameters

	glTexParameteri(GL_TEXUTRE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the active texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

}

`Selection of control points for editingSometimes, you would like to edit the mesh interactively by changing the control points. Specifically, we want to click on or "pick" a control point in the scene using the mouse. One way of doing this is to manually shoot a ray from the camera focus, through the projected pixel where the mouse clicks, and back to the 3D scene, and then check if that ray intersects with any control points. This is called Ray Picking. (You can also use it to pick 3D objects) Since points are pretty small in the space, we consider a point selected when the distance between the point and the ray is small enough.We begin with coordinates of the pixel the mouse selected. We can set up a call-back function for mouse event, or we can use glfwGetCursorPos() to get the position.Remember that such a coordinate is with respect to the screen, where the origin is to the left top corner of the window, and y is pointing downward. From this coordinate, you can shoot a ray out by using the use OpenGL function gluUnproject(). Figure 6 illustrates how to do the selection.                           Figure 6Once you have selected a control point, you want to drag it to somewhere else, and the surface will be automatically re-evaluated and re-meshed. Here you can think freely about how this editing can be designed as easily and conveniently as possible.Patching together multiple Bézier surfacesSeveral Bézier curves can be connected to together to form a longer curve. A 0-th order (L0) continuity means that the curves are connected only (the last and first points of the first and second curve are connected), but their tangents are not necessarily continuous. 1st order continuity (L1) means that not only the points are connected, but also their first-order tangents are continuous at the joint point. To ensure this, we need to make sure that the control polygon are colinear at the last point of the first curve and the first point of the second curve. For example, Figure 7 shows such a patching of two different Bézier curves, where red P1~P4 forms one Bézier curve and yellow PI~P4 form another curve. To ensure L1 continuity, we need to make sure that the red P3P4 and yellow P1P2 are colinear. It is similar to patch Bézier surfaces. As an optional work, you can think about how to patch multiple Bézier surfaces together to form a more complex shape, and use it to design more complex objects, such as teapot or cup.                           Figure 7Adaptive triangulationThe advantage of converting a Bézier surface into a triangle mesh is that we can use different numbers of triangles to approximate the true Bézier surface. However, not everywhere needs the same number of samples, for example, smooth areas may require less samples than steep areas. Thus, adaptive triangulation should be done to place smaller triangles in steeper regions and larger triangles in smooth regions. The whole number of samples is also dependent on the viewing distance to the object. In order to achieve this, some criteria such as the curvature of the surface or its distance to the camera should be first given. Then triangulation should be done adaptively according to the criteria, which is local. As an optional work, you can try to think about ways to adaptively triangulate the Bézier surface to give better triangulation.Skeleton programWe have prepared a skeleton code for you to do on both Windows and Linux, which you will need to augment it further on the implementation details and insert into your code of assignment 2. If you have any questions regarding configuration and algorithm understanding, you can resort to help from TAs.Technical reportFor technical report, we require you to do it with LaTex, and you can use TeXstudio to facilitate your editing. The latex template for your technical report can be downloaded here.
