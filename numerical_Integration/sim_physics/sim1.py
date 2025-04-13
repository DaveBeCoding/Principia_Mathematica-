import numpy as np
import pyvista as pv

# Step 1: Define your 3D scalar function
def f(x, y, z):
    return np.exp(-(x**2 + y**2 + z**2))  # Gaussian blob

# Step 2: Set integration bounds and resolution
x0, x1 = -1, 1
y0, y1 = -1, 1
z0, z1 = -1, 1
steps = 30

dx = (x1 - x0) / steps
dy = (y1 - y0) / steps
dz = (z1 - z0) / steps

x_vals = np.linspace(x0 + dx/2, x1 - dx/2, steps)
y_vals = np.linspace(y0 + dy/2, y1 - dy/2, steps)
z_vals = np.linspace(z0 + dz/2, z1 - dz/2, steps)

# Step 3: Sample the function and build voxel grid
voxels = []
scalars = []

for x in x_vals:
    for y in y_vals:
        for z in z_vals:
            val = f(x, y, z)
            if val > 0.01:  # Threshold to trim noise
                voxels.append([x, y, z])
                scalars.append(val)

points = np.array(voxels)
values = np.array(scalars)

# Step 4: Create a glyph representation of each voxel
grid = pv.PolyData(points)
grid["values"] = values

cube = pv.Cube(center=(0, 0, 0), x_length=dx, y_length=dy, z_length=dz)
glyphs = grid.glyph(scale=False, geom=cube)

# Step 5: Visualize the voxels
plotter = pv.Plotter()
plotter.add_mesh(glyphs, scalars="values", cmap="plasma", show_scalar_bar=True)
plotter.add_axes()
plotter.show_grid()
plotter.show()

# Step 6: Export for Blender or other software
glyphs.save("triple_integral_volume.obj")  # Can also export to STL or VTK
