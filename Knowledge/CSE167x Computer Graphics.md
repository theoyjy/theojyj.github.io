>[!INFO] History
>1. Overview3D Graphics Pipeline
>	Modeling -> Animation -> Rendering
>2. Modeling: Spline Curves -> More Recently: Triangle meshes
>3. Rendering:
>	1. 1960s: Hidden Line Algorithm | Hiden Surface Algorithm | Visibility 
>	 ![[CSE167x Computer Graphics-20240607001400360.webp|175]]![[CSE167x Computer Graphics-20240607001428324.webp|175]]
>	3. 1970s: Diffuse Lighting(散射光照) | Specular Lighting | Curved Surfaces, Texture | Z-Buffer Hidden Surface
>		1. Diffuse Lighting: make the polygonal outlines smooth
>		![[CSE167x Computer Graphics-20240607001643400.webp|175]]   ![[CSE167x Computer Graphics-20240607001732090.webp|175]]
>		2. Specular Light: enable highlights, makes it more realistic
>		![[CSE167x Computer Graphics-20240607002222038.webp|175]]
>		
>	1. 1980~90s: global illumination: ray tracing | radiosity | the rendering equation
>	![[CSE167x Computer Graphics-20240607002750611.webp|539]]

# Vector
>[!Tip] Cartesian Coordinates
>![[CSE167x Computer Graphics-20240609155159268.webp]]


>[!Abstract] 
>* About: length and direction. Absolute position not important
>* Used to store: 
>	* offsets(from a base point)
>	* displacements(the transformation from one position to another)
>	* and locations(coordiantes from 0 0 0)

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

>[!Warning] Corss Product
>	![[CSE167x Computer Graphics-20240609162309079.webp|251]]
> 1. Cross product orthogonal to two initial vectors
> 2. Direction determinted by **right-hand rule**
> 3. Useful in constructing coordinate system
> 	![[CSE167x Computer Graphics-20240609163243204.webp|370]]
> 	![[CSE167x Computer Graphics-20240612000950019.webp|370]]

>[!Danger] Orhonormal bases/coordinate frames
>1. Coordinates Frames: Any set of 3 vectors so that:
>	||u|| = ||v|| = ||w|| = 1
>	u * v = v * w = u * w = 0
>	w = u X v
>Any vector p can be expressed as:
> $$ \vec{p} = (\vec{p} · \vec{u}) · \vec{u} + (\vec{p} · \vec{v}) · \vec{v} +(\vec{p} · \vec{w} · \vec{v}
> $$
> 2. Constructing a coordinate frame
>	**通过点乘与叉乘，构建坐标系**
>	* give any two vector a and b
>	* get an axis from a vector: $$ w = \frac{a}{\|a\|} $$
>	* cannot get v right now, there is no proof that a is perpendicular to b, so get third axis by cross product of a b $$ u = \frac{b \times w}{\|b \times w\|} $$
>	* get the second one by $$ v = w \times u $$
>	* if a is parallel to b, u's divider would be 0, it cannot construct a coordinate out of it
>
>

>[!INFO] Matrix
>1. matrix-matrix multiplication
>	* not communitive, but associative and distributive
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

