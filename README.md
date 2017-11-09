# 一、问题描述

- 阅读论文,实现Image warping的两种方法
  - IDW(Inverse distance-weighted)方法
  - RBF(Radial basis functions)方法
- 使用QImage类四个接口函数width(), height(), pixel(), setPixel()

# 二、算法描述

## 1.反距离加权插值(IDW)算法

- 通过给定的一组控制点对，计算控制点间的位移矢量，实现图像每一个像素点的位移。
- 反距离加权插值(IDW)通过计算图片上每一个像素点和一组控制点对间的逼近关系以及权重关系，求得像素点变化之后的位置。
- 求解像素点变化的函数f(p)如下：

$$
f(p) = \sum^{n}_{i=1} w_i(p)f_i(p) \\\
其中w_i(p)是权重函数 \\
w_i(p_i) = 1 \ \ \ ,\sum^{n}_{i=1}w_i(p)=1 \ \ 且w_i(p) \ge 0 \ \ \ i=1,...,n  \\
w_i(p) = \frac{\sigma_{i}(p)}{\sum^{n}_{j=1} \sigma_j(p)} \ \ \ 且 \sigma_i(p) = \frac{1}{d(p,p_i)^{\mu}}  \\
f_i(p)为逼近函数 \\
f_i(p) = q_l + T_l(p-p_i)
$$

- T是一个2*2矩阵，可以取近似值1。将控制点数据代入可以求出每一个局部插值函数。 
- 这里d（p，pi）为p和$p_i$的距离，指数μ可以取>0的数，这里测试取2最优。通过公式求取权重函数，求和体现多组控制点共同产生影响。

## 2.径向基函数(RBF)算法



# 三、结果



# 四、总结