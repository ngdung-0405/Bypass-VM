#include <windows.h>
#include <iostream>

void simulateMouseMovement() {
    // Move the mouse across multiple points
    for (int x = 300; x <= 600; x += 50) {
        SetCursorPos(x, 400);
        Sleep(100);
    }
}

void simulateMouseClick() {
    // Simulate left mouse click
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void simulateDoubleClick() {
    // Simulate left mouse double click
    for (int i = 0; i < 2; ++i) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(50);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(100);
    }
}

void showDialogConfirmation() {
    // Show confirmation dialog
    int result = MessageBox(NULL, "Please confirm user interaction", "Pafish Mouse Bypass", MB_OKCANCEL | MB_ICONQUESTION);
    if (result == IDOK) {
        std::cout << "[+] User confirmed the dialog.\n";
    } else {
        std::cout << "[-] User did not confirm the dialog.\n";
    }
}

int main() {
    std::cout << "=== Bypassing Pafish mouse-related checks ===\n";

    simulateMouseMovement();
    Sleep(500);

    simulateMouseClick();
    Sleep(500);

    simulateDoubleClick();
    Sleep(500);

    showDialogConfirmation();

    std::cout << "=== Mouse simulation completed ===\n";
    return 0;
}
