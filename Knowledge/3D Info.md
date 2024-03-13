* 万向锁[无伤理解欧拉角中的“万向死锁”现象_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Nr4y1j7kn/?spm_id_from=333.337.search-card.all.click&vd_source=fd9ad5acee8ad5272946ea610756c3aa)
	* 形成原因：
		1. 旋转时局部坐标轴会跟着物体动
		2. 欧拉角会固定一个**旋转轴顺序**，以保证相同的rotation得到的结果一致
		3. 当y旋转90(为规避万向锁，一般选择最不可能成90的值成为中间轴)![[欧拉角万向锁.png]]，**在旋转完y轴90°后，z轴与起始态(0,0,0)的x轴一致，此时形成万向轴**

