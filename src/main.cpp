#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"



int main(int argc, char** argv) {
    try {
        MyWindow::Window window(800, 600, "Test", argv[0]);
        window.Run();
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
    
   

    
    return 0;
}
