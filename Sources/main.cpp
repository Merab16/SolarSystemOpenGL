#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Headers/Window.h"



int main() {
    try {
        MyWindow::Window window(800, 600, "Test");
        window.Run();
    }
    catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
    
   

    
    return 0;
}
