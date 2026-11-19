

## Compile and Run

Open PowerShell in the project folder:

```powershell
cd "C:\Users\ict\Desktop\Computer graphics"
```

### 1. Translation

```powershell
g++ translation.cpp -o translation -lgdi32
.\translation.exe
```

### 2. Rotation

```powershell
g++ rotation.cpp -o rotation -lgdi32
.\rotation.exe
```

### 3. Scaling

```powershell
g++ scaling.cpp -o scaling -lgdi32
.\scaling.exe
```

### 4. Reflection

```powershell
g++ reflection.cpp -o reflection -lgdi32
.\reflection.exe
```

### 5. Shearing

```powershell
g++ shear.cpp -o shear -lgdi32
.\shear.exe
```

**Important:** Close the graphics window before recompiling the same program.

## Main Working Mechanism

All five programs use the same basic drawing mechanism:

1. **Define vertices:** A triangle is created using three X and Y coordinate pairs: `(1,1), (4,1), (2,3)`.
2. **Apply transformation:** Mathematical formulas calculate the new coordinates.
3. **Create graphics window:** Win32 API creates a native Windows window.
4. **Draw coordinate system:** GDI draws the grid, X-axis, Y-axis, and coordinate labels.
5. **Draw triangles:** `CreatePen()` and `Polygon()` draw the original green triangle and transformed red triangle.
6. **Display results:** New coordinates are printed in the terminal.

### Transformation Formulas

| Transformation | Formula |
|---|---|
| Translation | x' = x + tx, y' = y + ty |
| Rotation | x' = x cosθ − y sinθ, y' = x sinθ + y cosθ |
| Scaling | x' = x × sx, y' = y × sy |
| Reflection (X-axis) | x' = x, y' = −y |
| X-Shear | x' = x + sh × y, y' = y |

## Default Input and Output

Original triangle: `(1,1), (4,1), (2,3)`

| Transformation | Input | Transformed Coordinates |
|---|---|---|
| Translation | tx=5, ty=3 | (6,4), (9,4), (7,6) |
| Rotation | 90° | (-1,1), (-1,4), (-3,2) |
| Scaling | sx=2, sy=2 | (2,2), (8,2), (4,6) |
| Reflection | X-axis | (1,-1), (4,-1), (2,-3) |
| Shearing | X-shear, sh=1 | (2,1), (5,1), (5,3) |

## Customization

Change the input values inside each `.cpp` file to test different transformations.

```cpp
float X[3] = {1, 4, 2};
float Y[3] = {1, 1, 3};
```

Save the file, compile again, and run.

## Troubleshooting

| Problem | Solution |
|---|---|
| `g++ not recognized` | Install MinGW and configure PATH. |
| `Permission denied` | Close the previous graphics window. |
| `graphics.h not found` | Use the Windows GDI version; `graphics.h` is not required. |
| Blank window | Resize or minimize and restore the window. |

**Note:** These programs are designed for learning and demonstrating fundamental 2D computer graphics transformations using C++ and Windows GDI.
