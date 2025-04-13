import numpy as np
import pyvista as pv
import time

# ------------------------------
# Step 1: Define a 3D Scalar Function
# Replace this with real scan data if needed
def f(x, y, z):
    return np.exp(-(x**2 + y**2 + z**2))  # 3D Gaussian blob

# ------------------------------
# Step 2: Define Volume Bounds and Resolution
x0, x1 = -1, 1
y0, y1 = -1, 1
z0, z1 = -1, 1
steps = 30  # Increase for higher resolution

dx = (x1 - x0) / steps
dy = (y1 - y0) / steps
dz = (z1 - z0) / steps

x_vals = np.linspace(x0 + dx / 2, x1 - dx / 2, steps)
y_vals = np.linspace(y0 + dy / 2, y1 - dy / 2, steps)
z_vals = np.linspace(z0 + dz / 2, z1 - dz / 2, steps)

# ------------------------------
# Step 3: Predefine Geometry and Plotter
cube = pv.Cube(center=(0, 0, 0), x_length=dx, y_length=dy, z_length=dz)
plotter = pv.Plotter()
plotter.show_grid()
plotter.add_axes()

# ------------------------------
# Step 4: Animate Slice-by-Slice Build Along Z-Axis
all_voxels = []
all_scalars = []

for z in z_vals:
    slice_voxels = []
    slice_scalars = []

    for x in x_vals:
        for y in y_vals:
            val = f(x, y, z)
            if val > 0.01:  # Threshold to trim noise
                slice_voxels.append([x, y, z])
                slice_scalars.append(val)

    if not slice_voxels:
        continue

    slice_points = np.array(slice_voxels)
    slice_values = np.array(slice_scalars)

    grid = pv.PolyData(slice_points)
    grid["values"] = slice_values
    glyphs = grid.glyph(scale=False, geom=cube)

    # Add current slice and render
    plotter.add_mesh(glyphs, scalars="values", cmap="plasma", opacity=1.0)
    plotter.render()
    time.sleep(0.5)  # Simulate animation delay # MOD -> .01 og value

    # Save for export
    all_voxels.extend(slice_voxels)
    all_scalars.extend(slice_scalars)

# ------------------------------
# Step 5: Final Export
# Rebuild full glyphs for export after all slices rendered
full_grid = pv.PolyData(np.array(all_voxels))
full_grid["values"] = np.array(all_scalars)
full_glyphs = full_grid.glyph(scale=False, geom=cube)

# Export to file (Blender-compatible)
full_glyphs.save("triple_integral_volume.obj")
print("✅ 3D volume exported as 'triple_integral_volume.obj'")
plotter.show()
