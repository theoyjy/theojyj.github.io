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

