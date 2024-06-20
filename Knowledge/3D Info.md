* 万向锁[无伤理解欧拉角中的“万向死锁”现象_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Nr4y1j7kn/?spm_id_from=333.337.search-card.all.click&vd_source=fd9ad5acee8ad5272946ea610756c3aa)
	* 形成原因：
		1. 旋转时局部坐标轴会跟着物体动
		2. 欧拉角会固定一个**旋转轴顺序**，以保证相同的rotation得到的结果一致
		3. 当y旋转90(为规避万向锁，一般选择最不可能成90的值成为中间轴)![[欧拉角万向锁.png|584]]，**在旋转完y轴90°后，z轴与起始态(0,0,0)的x轴一致，此时形成万向轴**
## View Matrix
[深入理解透视矩阵](https://www.zhyingkun.com/perspective/perspective/)
1. 正交矩阵
	![[3D Info-20240430134824853.webp|552]]
2. 投影矩阵：$Mpersp = Mpersp->ortho * Mortho$
	![[3D Info-20240430134709925.webp|430]]
	![[3D Info-20240430135551269.webp]]
3. Aspect Ration & FOV
	![[3D Info-20240430135918310.webp]]
	$tan(fovV/2)=(height/2)/n$ -> $height = fovV/2$
4. 已知fov, aspect ratio, zNear, zFar, 求投影矩阵
```cpp
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,  
                                      float zNear, float zFar)  
{  
    // Students will implement this function  
  
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();  
  
    // TODO: Implement this function  
    // Create the prospective projection matrix for the given parameters.    // Then return it.  
    float top = zNear * tan(eye_fov/2);  
    float right = top * aspect_ratio;
    
    projection << 
	    1/(aspect_ratio*tan(eye_fov/2)), 0, 0, 0,  
        0, 1/tan(eye_fov/2), 0, 0,
        0, 0, (zNear+zFar)/(zNear-zFar), 2*zNear*zFar/(zNear-zFar),
        0, 0, -1, 0;  
        
    return projection;  
}
```