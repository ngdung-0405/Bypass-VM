#include <windows.h>
#include <iostream>
#include <cstdlib>  // cho rand()
#include <ctime>    // cho time()
#include <cmath>    // cho fabs (tính khoảng cách)

// Hàm simulate single click
void SimulateSingleClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

// Hàm simulate double click
void SimulateDoubleClick() {
    SimulateSingleClick();
    Sleep(50);  // Delay nhỏ giữa 2 click
    SimulateSingleClick();
}

// Hàm di chuyển chuột dần dần đến vị trí mới để tránh supernatural speed
void SmoothMoveTo(int targetX, int targetY) {
    POINT currentPos;
    GetCursorPos(&currentPos);  // Lấy vị trí hiện tại

    int steps = 20 + rand() % 21;  // Số bước ngẫu nhiên 20-40 để mimic tự nhiên
    double deltaX = (targetX - currentPos.x) / static_cast<double>(steps);
    double deltaY = (targetY - currentPos.y) / static_cast<double>(steps);

    for (int i = 1; i <= steps; ++i) {
        int newX = currentPos.x + static_cast<int>(deltaX * i);
        int newY = currentPos.y + static_cast<int>(deltaY * i);
        SetCursorPos(newX, newY);
        Sleep(10 + rand() % 11);  // Delay nhỏ 10-20ms mỗi bước, tổng tốc độ ~100-200px/s
    }
}

// Hàm tìm và click button "OK" trong dialog bằng chuột
void HandleDialog() {
    HWND dialogHwnd = FindWindow(NULL, TEXT("Pafish RTT window"));
    if (dialogHwnd != NULL) {
        // Tìm handle của button "OK" (class "Button", text "OK")
        HWND okButtonHwnd = FindWindowEx(dialogHwnd, NULL, TEXT("Button"), TEXT("OK"));
        if (okButtonHwnd != NULL) {
            // Lấy vị trí button
            RECT buttonRect;
            GetWindowRect(okButtonHwnd, &buttonRect);
            int buttonX = buttonRect.left + (buttonRect.right - buttonRect.left) / 2;  // Giữa button
            int buttonY = buttonRect.top + (buttonRect.bottom - buttonRect.top) / 2;

            // Di chuyển chuột dần dần đến button
            SmoothMoveTo(buttonX, buttonY);
            Sleep(200);  // Delay mimic người dùng nhìn và quyết định

            // Click vào button
            SimulateSingleClick();
            std::cout << "Handled dialog confirmation by clicking OK button." << std::endl;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));  // Seed random
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int dialogCheckInterval = 0;

    std::cout << "Running mouse simulator. Press Ctrl+C to stop." << std::endl;

    while (true) {
        // Di chuyển chuột ngẫu nhiên dần dần
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;
        SmoothMoveTo(x, y);
        Sleep(rand() % 2501 + 500);  // Delay 500-3000ms giữa các movement lớn

        // Single click (50% chance)
        if (rand() % 10 < 5) {
            SimulateSingleClick();
            Sleep(rand() % 401 + 100);  // Delay 100-500ms
        }

        // Double click (30% chance)
        if (rand() % 10 < 3) {
            SimulateDoubleClick();
            Sleep(rand() % 401 + 100);  // Delay 100-500ms
        }

        // Kiểm tra dialog mỗi 5 giây
        dialogCheckInterval++;
        if (dialogCheckInterval >= 5) {
            HandleDialog();
            dialogCheckInterval = 0;
        }
    }
    return 0;
}