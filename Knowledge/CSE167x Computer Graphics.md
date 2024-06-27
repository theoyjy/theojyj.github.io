# History
1. Overview 3D Graphics Pipeline
	Modeling -> Animation -> Rendering
2. Modeling: Spline Curves -> More Recently: Triangle meshes
3. Rendering:
	1. 1960s: Hidden Line Algorithm | Hiden Surface Algorithm | Visibility 
	 ![[CSE167x Computer Graphics-20240607001400360.webp|175]]![[CSE167x Computer Graphics-20240607001428324.webp|175]]
	3. 1970s: Diffuse Lighting(散射光照) | Specular Lighting | Curved Surfaces, Texture | Z-BufferHidden Surface
		1. Diffuse Lighting: make the polygonal outlines smooth
		![[CSE167x Computer Graphics-20240607001643400.webp|175]]   ![[CSE167x Computer Graphics-20240607001732090.webp|175]]
		2. Specular Light: enable highlights, makes it more realistic
		![[CSE167x Computer Graphics-20240607002222038.webp|175]]
		
	1. 1980~90s: global illumination: ray tracing | radiosity | the rendering equation
	![[CSE167x Computer Graphics-20240607002750611.webp|539]]

# Vector
>[!Tip] Cartesian Coordinates
>![[CSE167x Computer Graphics-20240609155159268.webp]]

>[!Abstract] 
>* About: length and direction. Absolute position not important
>* Used to store: 
>	* offsets(from a base point)
>	* displacements(the transformation from one position to another)
>	* and locations(coordiantes from 0 0 0)

## Dot Product
> [!Warning] Dot Product a · b = b · a = |a| |b| cos
> $$
  \vec{a} · \vec{b} = \begin{bmatrix} xa \\ ya \end{bmatrix} · \begin{bmatrix} xb \\ yb \end{bmatrix} = xa*xb*\vec{x} + (...) * \vec{x} * \vec{y} + ya * ya * \vec{y}$$
  > 由于向量x与向量y垂直，点乘的结果是0,所以
  >$$  \vec{a} · \vec{b} = \vec{xa} * \vec{xb} + \vec{ya} * \vec{yb} $$
  >* **Applications:**
  >1. Finding angle between two vectors (r.g. cos of angle between light source and surface of shading)
  >2. Finding projection of one vector on another(e.g. coordinates of point in arbitrary coordinate system)
  >	![[CSE167x Computer Graphics-20240609161559302.webp|430]]
  >Advanteges: easily computed in cartesian components

## Cross Product
>[!Warning] Corss Product
>![[CSE167x Computer Graphics-20240609162309079.webp|251]]
> 1. Cross product orthogonal to two initial vectors
> 2. Direction determinted by **right-hand rule**
> 3. Useful in constructing coordinate system
> 	![[CSE167x Computer Graphics-20240609163243204.webp|370]]
> 	![[CSE167x Computer Graphics-20240612000950019.webp|370]]

# Orthogonal bases/coordinate frames
>[!INFO]
>1. Coordinates Frames: Any set of 3 vectors so that:
>$$
>\begin{align}
>	&||u|| = ||v|| = ||w|| = 1\\
>	&u \times v = v \times w = u \times w = 0\\
>	&w = u \times v
>\end{align}
>$$
>1. Any vector p can be expressed as:>$$ \vec{p} = (\vec{p} · \vec{u}) · \vec{u} +(\vec{p} · \vec{v}) · \vec{v} (\vec{p} · \vec{w} · \vec{v}$$
>2. Constructing a coordinate frame
>	* **通过点乘与叉乘，构建坐标系**:
>		* give any two vector a and b
>		* get an axis from a vector: $$ w = \frac{a}{\|a\|} $$
>		* cannot get v right now, there is no proof that a is perpendicular to b, so get third axis by **cross product of a b** $$ u = \frac{b \times w}{\|b \times w\|} $$
>		* get the second one by $$ v = w \times u $$
>	* if a is parallel to b, u's divider would be 0, it cannot construct a coordinate out of it

# Matrix
>[!INFO] 
>1. matrix-matrix multiplication
>	* not commutative, but associative and distributive
>![[CSE167x Computer Graphics-20240619223826876.webp]]
>2. matrix-vector multiplication 【key for transforming points】
>	![[CSE167x Computer Graphics-20240619224515305.webp|268]]
>3. Transpose of a matrix
>	![[CSE167x Computer Graphics-20240619224633506.webp|235]]
>4. Identity Matrix and Inverses
>![[CSE167x Computer Graphics-20240619224832683.webp|191]]
>5. Dot product and Cross product in Matrix
>	1. ⭐ Dot: a \* b = b \* a = aTb = bTa
>	![[CSE167x Computer Graphics-20240619225030404.webp|502]]

## Transformation Matrix in Carsidian Coordinates
>[!Tip] Transformation
>1. scale 
>	 ![[CSE167x Computer Graphics-20240620162949480.webp|415]]
>2. shear
>	 ![[CSE167x Computer Graphics-20240620163202142.webp|504]]
>3. ⭐Rotate R(X + Y) = R(X) + R(Y) **Not Communative**
>	1. 2D 旋转矩阵推导
>		![[CSE167x Computer Graphics-20240620164704196.webp|505]]
>	2. Rotations in 3D
>		![[CSE167x Computer Graphics-20240620175428618.webp|515]]
>	3. Geometric Interpretation 3D Rotations
>		* u v w为新坐标系的三个单位坐标，相互垂直
>		![[CSE167x Computer Graphics-20240620175522483.webp]]
>	4. Rotate vec b about an arbitary axis with theta degree:
>		[Rodrigues Rotation Fomula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula)
>		![[CSE167x Computer Graphics-20240621140957957.webp|520]]
>		![[CSE167x Computer Graphics-20240621141126264.webp]]
## Inverse and Transpose Matrix
>[!DANGER] 逆 与 转置
>1. 逆矩阵也就是矩阵的还原矩阵：R\*R-1 = I
>	1. 对于旋转矩阵，它的逆就是把角度在转回来
>	2. 对于缩放矩阵，它的逆就是把缩放大小再还原回来
>2. 转置矩阵就是矩阵的翻转矩阵，沿着左上到右下的对角线翻转
>3. 旋转矩阵
>	1. 旋转矩阵的逆 = 旋转矩阵的转置
>	2. 旋转矩阵的逆的转置 = 旋转矩阵自身
>	![[CSE167x Computer Graphics-20240621134542669.webp|619]]

# Homogeneous Coordinates
>[!ABSTRACT] Intro
>1. 在齐次坐标中，坐标 (x, y, z, w) 表示的实际点是 (x/w, y/w, z/w)。
>2. 当 w=1 时，齐次坐标 (x, y, z, w) 直接对应于笛卡尔坐标 (x, y, z)。
>3. 当 w=0 时，齐次坐标表示的是一个方向而不是一个点，这在表示视线和光线等概念时非常有用。
>
>Advantages:
>1. Unified framework for translation, viewing, rot… 
>2. Can concatenate any set of transforms to 4x4 matrix 
>3. No division (as for perspective viewing) till end 
>4. Simpler formulas, no special cases § Standard in graphics software, hardware

## Transform Matrix in Homogeneous Coordinates
>[!TIP] General Translation Matrix T
>$$
>T=
>\begin{bmatrix}  
1 & 0 & 0 & t_x \\  
0 & 1 & 0 & t_y \\  
0 & 0 & 1 & t_z \\  
0 & 0 & 0 & 1  
\end{bmatrix}
>=
>\begin{bmatrix}
>I3 & T \\
>0 & 1
>\end{bmatrix}
>$$
>$$
P'=TP = 
\begin{bmatrix}  
1 & 0 & 0 & t_x \\  
0 & 1 & 0 & t_y \\  
0 & 0 & 1 & t_z \\  
0 & 0 & 0 & 1  
\end{bmatrix}  
\begin{bmatrix}  
x \\  
y \\  
z \\  
1  
\end{bmatrix}  
=  
\begin{bmatrix}  
x + t_x \\  
y + t_y \\  
z + t_z \\  
1  
\end{bmatrix}
>=P+T
$$

### Combining Translations, Rotations
>[!DANGER]
>1. Rotate first, then Translate
>$$P'=(TR)P=MP=RP+T$$
>$$
>T=\begin{bmatrix}I3 & T\\0 & 1\end{bmatrix}
>\quad 
>R=\begin{bmatrix}R & 0 \\ 0 & 1 \end{bmatrix}
>$$
>$$
>\begin{align}
>M &= TR = 
>	\begin{bmatrix}
>		I3 & T \\
>		0 & 1
>	\end{bmatrix}
>	\begin{bmatrix}
>		R & 0 \\
>		0 & 1
>	\end{bmatrix}
>   =
>	\begin{bmatrix}
>		R & T \\
>		0 & 1
>	\end{bmatrix} \\
>   &=
>   \begin{bmatrix}
>		R11 & R12 & R13 & Tx\\
>		R21 & R22 & R23 & Ty\\
>		R31 & R32 & R33 & Tz \\
>		0 & 0 & 0 & 1
>	\end{bmatrix}
>\end{align}
>$$
>
>2. Translate first, then Rotate
>
>$$P' = (RT)P = MP = R(P + T) = RP + RT$$
>$$
>M = RT = 
>	\begin{bmatrix}
>	R & 0 \\
>	0 & 1
>	\end{bmatrix}
>	\begin{bmatrix}
>	I3 & T \\
>	0 & 1
>	\end{bmatrix}
>   =
>    \begin{bmatrix}
>	R_{3 \times 3} & R_{3 \times 3}T_{3 \times 1} \\
>	0 & 1
>	\end{bmatrix}
>$$
>$$
>MP = 
>    \begin{bmatrix}
>		R & RT \\
>		0 & 1
>	\end{bmatrix}
>	\begin{bmatrix}
>		P \\
>		1
>	\end{bmatrix} 
>   =
>   \begin{bmatrix}
>		RP + RT \\
>		1
>	\end{bmatrix}
>	=
>   \begin{bmatrix}
>		R_{3\times3}P_{3\times1} \\
>		0
>	\end{bmatrix}
>	+
>   \begin{bmatrix}
>		R_{3\times3}T_{3\times1} \\
>		1
>	\end{bmatrix}
>$$
>
### Transforming Normals
>[!DANGER] 
> For any point P:
> * t denotes for tangent of that point
> * n denotes for the normal, which n is perpendicular to t
> * After some actions $$t -> Mt, \quad n -> Qn \quad => \quad Q = (M^{-1})^{T}$$
>![[CSE167x Computer Graphics-20240621193317063.webp]]

### Rotate Coordinate Frames
![[CSE167x Computer Graphics-20240621194938476.webp]]
#### `gluLookAt`
>[!INFO]
>* ![[CSE167x Computer Graphics-20240625164620892.webp|215]]
>1. Create a coordinate frame for camera [T first]
>2. Define a rotation matrix [R second]
>> 在3D图形中，我们通常使用三个正交向量（right、forward、up）来定义一个局部坐标系或者说是一个物体的方向。这三个向量通常被称为物体的基向量（basis vectors）。这三个向量的方向分别对应于物体的右方、前方和上方。  当我们想要在3D空间中旋转一个物体时，我们可以使用这三个基向量来构建一个旋转矩阵。这个旋转矩阵可以将物体从其当前的方向旋转到新的方向。  构建旋转矩阵的方法是将这三个基向量作为旋转矩阵的列（或行，取决于你使用的是行主序还是列主序）。**因此只需获得camera的right, foward,up vector:**
>> $$R = \begin{bmatrix}
>> right.x & right.y & right.z & 0 \\
>> forward.x & forward.y & forward.z & 0 \\
>> up.x & up.y & up.z & 0 \\
>> 0 & 0 & 0 & 1
>> \end{bmatrix}$$
>$$P'=(TR)P=MP=RP+RT$$
>4. Apply appropriate translation for camera location
>![[CSE167x Computer Graphics-20240625165840561.webp|312]]
>
>To summarize, the `gluLookAt` matrix can be thought of as a **translation followed by a rotation** because:
>
>* We first translate the scene to position the camera at the origin.
>* Then, we apply a rotation to align the camera's view direction with the default viewing direction in OpenGL (looking along the negative z-axis).



# Viewing
## Orthographic Matrix
>[!IMPORTANT] 
>![[CSE167x Computer Graphics-20240625171558662.webp|455]]
>**The length of scaled cuboid is 2**, so that each vertex can be at 1 from origin
>$$
>\begin{align}
>Scale \quad \quad \quad \quad & Translation(centering)\\
>M = \begin{bmatrix}
>	2 \over r-l & 0 & 0 & 0 \\
>	0 & 2 \over t-b & 0 & 0 \\
>	0 & 0 & 2 \over f-n & 0 \\
>	0 & 0 & 0 & 1
>	\end{bmatrix}
>	&\begin{bmatrix}
>	1 & 0 & 0 & - (l+r) \over 2 \\
>	0 & 1 & 0 & - (t+b) \over 2 \\
>	0 & 0 & 1 & - (f+n) \over 2 \\
>	0 & 0 & 0 & 1
>	\end{bmatrix}
>   = \begin{bmatrix}
>	2 \over r-l & 0 & 0 & - (l+r) \over r-l\\
>	0 & 2 \over t-b & 0 & - (t+b) \over t-b \\
>	0 & 0 & 2 \over f-n & - (f+n) \over f-n \\
>	0 & 0 & 0 & 1
>	\end{bmatrix}
>\end{align}
>$$
>However, OpenGL looking down -z, so f and n are both negative(n is nearer to 0 => n > f)
>	To make n, f poistive, the scale z is negative:
>$$
> glOrtho = \begin{bmatrix}
>	2 \over r-l & 0 & 0 & - (l+r) \over r-l\\
>	0 & 2 \over t-b & 0 & - (t+b) \over t-b \\
>	0 & 0 & -2 \over f-n & - (f+n) \over f-n \\
>	0 & 0 & 0 & 1
>	\end{bmatrix}
>$$

## Perspective Projecttion
>[!success] 
>Overhead view of Our Screen(negation of z coord focal plane d):
>![[CSE167x Computer Graphics-20240625203953203.webp|476]]
>Projection Matrix (Only last row affected. w will no longer =1,Must divide at th end )
>$$
>p=\begin{bmatrix}
>1 & 0 & 0 & 0 \\
>0 & 1 & 0 & 0 \\
>0 & 0 & 1 & 0 \\
>0 & 0 & -1 \over d & 0 \\
>\end{bmatrix}
>$$
>$$
>\begin{bmatrix}
>	1 & 0 & 0 & 0 \\
>	0 & 1 & 0 & 0 \\
>	0 & 0 & 1 & 0 \\
>	0 & 0 & -1 \over d & 0 \\
>\end{bmatrix}
>\begin{bmatrix}
>x\\ y\\ z\\1
>\end{bmatrix}
>=
>\begin{bmatrix}
>x\\ y\\ z\\-z\over d
>\end{bmatrix}
>\begin{bmatrix}
>-d*x \over z \\ -d*y\over z\\ -d \\1
>\end{bmatrix}
>$$

>[!TIP]
>Orthographic projection preserves parallel lines by definition.
Perspective projection will not preserve parallel lines.

### gluPerspective
>[!Danger] 
>* fov and aspect ratio
![[CSE167x Computer Graphics-20240625212159405.webp|435]]
![[CSE167x Computer Graphics-20240625212330021.webp|370]]
> Perpective project:
> 1. Apsect ratio taken into account
> 2. Homogeneous, simpler to multiply through by d
> 3. must map z vals based on near and far planes
> $$
> P = \begin{bmatrix}
>1 \over aspect & 0 & 0 & 0 \\
>0 & 1 & 0 & 0 \\
>0 & 0 & 1 & 0 \\
>0 & 0 & -1 \over d & 0 \\
>\end{bmatrix}
>->\begin{bmatrix}
>d \over aspect & 0 & 0 & 0 \\
>0 & d & 0 & 0 \\
>0 & 0 & A & B \\
>0 & 0 & -1 & 0 \\
>\end{bmatrix}
> $$
> where A and B selected to map n and f to -1, +1 respectively
>>Deduction of A and B:
>>$$
>>\begin{bmatrix}
>>A & B \\
>>-1 & 0
>>\end{bmatrix}
>>\begin{bmatrix}
>>z \\ 1
>>\end{bmatrix}=
>>\begin{bmatrix}
>>Az + B \\ -z
>>\end{bmatrix}=
>>\begin{bmatrix}
>>-A - \frac{B}{z} \\ 1
>>\end{bmatrix}
>>$$
>> when z = n, $$ -A \frac{B}{n} = -1 $$
>> when z = f, $$ -A \frac{B}{f} = 1 $$
>> Overall, we get:
>> $$
>> A = -\frac{f+n}{f-n} \quad B = - \frac{2fn}{f-n}
>> $$
>
>
>So,
>$$
>P = \begin{bmatrix}
>d \over aspect & 0 & 0 & 0 \\
>0 & d & 0 & 0 \\
>0 & 0 & -\frac{f+n}{f-n} & - \frac{2fn}{f-n} \\
>0 & 0 & -1 & 0 \\
>\end{bmatrix}
>$$
>


# Homework 1
## Basic GLM(OpenGL Mathmatics)
### Matrix Column Major
>[!TIP] Caveats on Row vs **Column Major**
>$$
>\begin{bmatrix}
>a & b &c \\ d & e & f \\ g & h & i
>\end{bmatrix}
>$$
>1. **Would be defined as** `glm::mat3(a,d,g,b,e,g,c,f,i)`
>2. Alternaticely, `glm:mat3 m(a,b,c,d,e,f,g,h,i); m = glm::transpose(m);`

>[!DANGER] 
>In a typical 3D graphics setup, the coordinate system is right-handed with:
>1. Right: the X-axis pointing to the right of screen
>2. Up: the Y-axis pointing up of the screen (This is why the up vector is often initialized as (0, 1, 0)
>3. Forward: the Z-axis pointing out of the screen. 
>R = [Right,
>	Up,
>	Forwad]

# OpenGL
>[!INFO] Benefits
>1. Encapusulates many basic functions of 2D/3D graphics
>2. Think of it as high-level language(C++) for graphics

## OpenGL Rendering Pipeline

 >[!IMPORTANT] OpenGl is a scan converter rasterizer
![[CSE167x Computer Graphics-20240627231411792.webp]]
 >1. **Geometry Primitive Operations 基本几何运算**
 >2. **Scan Conversion(Rasterize) 扫描转换(光栅化)** : Decide ==which pixel correspond which part of geomery==
 >3. **Fragment operations**:  refer to a series of steps that **each fragment (a potential pixel)** undergoes before it is written to the framebuffer. Includingg various tests and manipulations that determine ==whether a fragment should be drawn== and ==how it should be combined with the existing content in the framebuffer==.

### Shader

 >[!Abstract] 
 >* **Definition**: A small piece of program that runs on the GPU and used to control various stages of the graphics rendering process.
 >* **The main purpose** of a shader: is to manipulate vertices, pixels(fragments), and geometry to achieve various visual effects.
 >* Common types:
 >	* vertex shader
 >	* fragment shader

 >[!success] Vertex Shader
 >Translate vertex positions in 3D  -> 2D screen coordiante system and to transform the attributes of vertices (such as colors, normals, textures, etc.)
 >Core steps:
 >1. Model Transformation: ==model== coordinate system -> ==world== coordinate system
 >2. View Transformation: world coordinate system -> ==camera==(view) coordinate system
 >	* OpenGL always make: ==the camera is the origin, looking down the -z axis==.
 >3. Projection Transformation: view coord -> ==cropped== space coordinate system
 >4. Perspective Division: cropped space coord -> ==screen== coordinate system
 
>[!SUCCESS] Fragment Shader
> Calculate the final colour of each fragment and output it to the frame buffer.
> The main functions of the fragment shader include:
>1. Texture sampling: ==obtaining colour== information from the texture.
>2. Light Calculation: ==calculates the colour== of the fragment based on the ==lighting== model.
>3. Colour ==mixing==: mixes the calculated colour with the existing frame buffer colour (e.g. to achieve transparency effects)
>>[!TIP] Fragment operations
>>```cpp
>>// Enable depth test
>>// whether the depth value of the fragment is written to the depth buffer
>>glEnable(GL_DEPTH_TEST);
>>glDepthFunc(GL_LESS);
>>
>>// Enable stencil test
>>// The stencil buffer is a per-pixel buffer that can store an integer value. The >stencil test >compares the stencil value with a reference value using a specified >function (like less than, >equal to, etc.). If the test fails, the fragment is >discarded.
>>glEnable(GL_STENCIL_TEST);
>>glStencilFunc(GL_EQUAL, 1, 0xFF);  // Pass test if (stencil & 0xFF) == 1
>>glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // Actions based on stencil test result
>>
>>// Enable blending
>>// Blending determines how the fragment's color should be combined with the color >already in >the framebuffer. This is crucial for achieving transparency and other >effects.
>>// Blending operations combine the source (fragment) color with the destination >(framebuffer) >color based on specified blending factors.
>>glEnable(GL_BLEND);
>>glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
>>
>>// Enable scissor test
>>// whether the fragment lies within a defined rectangular region. If the fragment >is outside this >region, it is discarded.
>>glEnable(GL_SCISSOR_TEST);
>>glScissor(50, 50, 200, 200);  // Define scissor box
>>
>>// Configure color mask
>>// whether the red, green, blue, and alpha components of the fragment are written >to the >framebuffer.
>>glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
>>
>>// Configure depth mask
>>// whether the depth value of the fragment is written to the depth buffer.
>>glDepthMask(GL_TRUE);
>>
>>// Configure stencil mask
>>// which bits of the stencil value can be written to the stencil buffer.
>>glStencilMask(0xFF);
>>```
>

## BUFFERS AND MATRICES
