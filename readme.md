# This Project is not final and can be changed 
## This Project belongs to Galaxy64 and only for learning purpose for Graphics API(OpenGL)
- Anyone can use it as reference, I wont recommed it as my code struture is not that good
- For Window Creating GLFW and GLAD are used with Core OpenGL library v330
- If you say somewhere in angular brackets and its empty or like this thing or that then i'll update. There would be cases i forget to add the file or script so anyone can just add a request or add a line to communicate in ```Message.txt``` or  ```Message.md```  in Folder A_MessageByUsers and use " Dates when someone write changes " or not.
- And lastly I need help me by writing some suggestions in message file like this : `Suggestion(/* Suggestion */)`.

# To build
run ` ./build.sh` for linux users
run ` g++ -std=c++17 main.cpp glad/src/glad.c imgui/*.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp -o main_glfw -Iglad/include -Iimgui -Iimgui/backends -lglfw -lGL -ldl && ./main_glfw  ` for windows users in src folder
- use cmake to build (for VS code just use cmake extension to build and run)