#include <windows.h>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

// ===== INPUT =====
float X[3] = {1, 4, 2};
float Y[3] = {1, 1, 3};
int ch = 1;         // 1 = X-Shear, 2 = Y-Shear
float sh = 1;       // shear factor
// =================

float NX[3], NY[3];
const int U = 36;
int OX, OY;

int px(float v) { return OX + (int)lround(v * U); }
int py(float v) { return OY - (int)lround(v * U); }

void drawLine(HDC dc, int x1, int y1, int x2, int y2, COLORREF c, int w) {
    HPEN p = CreatePen(PS_SOLID, w, c);
    HGDIOBJ old = SelectObject(dc, p);
    MoveToEx(dc, x1, y1, NULL);
    LineTo(dc, x2, y2);
    SelectObject(dc, old);
    DeleteObject(p);
}

void drawText(HDC dc, int x, int y, const char* s) {
    TextOutA(dc, x, y, s, strlen(s));
}

void drawTriangle(HDC dc, float x[], float y[], COLORREF c) {
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        drawLine(dc, px(x[i]), py(y[i]), px(x[j]), py(y[j]), c, 3);
    }
}

LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        RECT r;
        GetClientRect(h, &r);
        OX = r.right / 2;
        OY = r.bottom / 2;
        SetBkMode(dc, TRANSPARENT);

        for (int i = -OX / U; i <= OX / U; i++) drawLine(dc, px(i), 0, px(i), r.bottom, RGB(225, 225, 225), 1);
        for (int i = -OY / U; i <= OY / U; i++) drawLine(dc, 0, py(i), r.right, py(i), RGB(225, 225, 225), 1);

        drawLine(dc, 0, OY, r.right, OY, RGB(0, 0, 0), 2);
        drawLine(dc, OX, 0, OX, r.bottom, RGB(0, 0, 0), 2);
        drawText(dc, r.right - 15, OY - 20, "X");
        drawText(dc, OX + 6, 2, "Y");
        drawText(dc, OX - 12, OY + 4, "0");

        // numbers 1 to 8 on all four sides
        char b[10];
        for (int i = 1; i <= 8; i++) {
            sprintf(b, "%d", i);
            drawText(dc, px(i) - 4, OY + 4, b);        // right
            drawText(dc, OX + 6, py(i) - 7, b);        // up
            sprintf(b, "-%d", i);
            drawText(dc, px(-i) - 8, OY + 4, b);       // left
            drawText(dc, OX + 6, py(-i) - 7, b);       // down
        }

        drawTriangle(dc, X, Y, RGB(0, 170, 0));
        drawTriangle(dc, NX, NY, RGB(255, 0, 0));
        drawText(dc, 10, 10, "Green = Original, Red = Sheared");
        EndPaint(h, &ps);
        return 0;
    }
    if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProcA(h, m, w, l);
}

int main() {
    // Shear
    for (int i = 0; i < 3; i++) {
        if (ch == 1)      { NX[i] = X[i] + sh * Y[i]; NY[i] = Y[i]; }   // X-shear
        else if (ch == 2) { NX[i] = X[i]; NY[i] = Y[i] + sh * X[i]; }   // Y-shear
        else { cout << "Invalid choice!\n"; return 1; }
    }

    cout << "Shear (choice " << ch << ", factor " << sh << ")\nNew coordinates:\n";
    for (int i = 0; i < 3; i++) cout << "(" << NX[i] << ", " << NY[i] << ")\n";

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "GfxWin";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassA(&wc);
    CreateWindowA("GfxWin", "Shear", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 50, 900, 650, NULL, NULL, wc.hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
