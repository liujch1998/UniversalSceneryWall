import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection

file_in = open(sys.argv[1], "r")
nums = [float(num) for num in file_in.read().split()]
ptr = 0

frame_x = nums[ptr]
ptr += 1
frame_y = nums[ptr]
ptr += 1

polygon_cnt = int(nums[ptr])
ptr += 1
patches = []
layers = []
layer_cnt = 0
for i in range(polygon_cnt):
    layer = int(nums[ptr])
    ptr += 1
    vertex_cnt = int(nums[ptr])
    ptr += 1
    vertexs = np.zeros((vertex_cnt,2))
    for j in range(vertex_cnt):
        vertexs[j][0] = nums[ptr]
        ptr += 1
        vertexs[j][1] = nums[ptr]
        ptr += 1
    patches.append(Polygon(vertexs, True))
    layers.append(layer)
    layer_cnt = max(layer_cnt, layer + 1)

fig,ax = plt.subplots()
pc = PatchCollection(patches, alpha=1.0)
pc.set_array(np.array(layers))

ax.add_collection(pc)
plt.axis([0,frame_x, 0,frame_y])
plt.savefig(sys.argv[2])

for layer_index in range(layer_cnt):
    fig,ax = plt.subplots()
    pc = PatchCollection([patches[i] for i in range(polygon_cnt) if layers[i]==layer_index], alpha=0.4)
    pc.set_array(np.array([layers[i] for i in range(polygon_cnt) if layers[i]==layer_index]));
    
    ax.add_collection(pc)
    plt.axis([0,frame_x, 0,frame_y])
    plt.savefig(str(layer_index) + '.png')
