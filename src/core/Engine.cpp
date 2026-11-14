#include "core/Engine.hpp"

EngineContext context;

enum Errors {
    GLAD_Loader_Failed = -3, Window_Failed = -2, GLFW_init_Failed = -1
};


Engine::Engine(){}

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// square
ObjectData square;
// triangle
ObjectData triangle;
// cube
ObjectData cube;
// sphere
ObjectData sphere;
// pyramid
ObjectData pyramid;
// Light
ObjectData light;

//! ----------------------------
//!                            |
//!         INIT OPENGL        |
//!                            |
//!----------------------------|
void Engine::OPENGL_INIT() {

    GenerateSquareData(square, false, true);
    square.shader = new Shader("resources/shaders/test.vs", "resources/shaders/test.fs");
    square.texture = new Texture("resources/textures/container.jpg");


    GenerateTriangleData(triangle, false, true);
    triangle.shader = new Shader("resources/shaders/test.vs", "resources/shaders/test.fs");
    triangle.texture = new Texture("resources/textures/container.jpg");
    

    GenerateCubeData(cube, false, true);
    cube.shader = new Shader("resources/shaders/cube.vs", "resources/shaders/cube.fs");
    cube.texture = new Texture("resources/textures/container.jpg");


    GenerateSphereData(sphere, 2.0f, 36, 18, false, true);
    sphere.shader = new Shader("resources/shaders/test.vs", "resources/shaders/test.fs");
    sphere.texture = new Texture("resources/textures/container.jpg");


    std::vector<float> pyramidVertices = {
        // Base (1 triangle)
        -0.5f, 0.0f, -0.5f,
        0.5f, 0.0f, -0.5f,
        0.0f, 0.0f,  0.5f,

        // Front-Left face
        -0.5f, 0.0f, -0.5f,
        0.0f, 0.0f,  0.5f,
        0.0f, 1.0f,  0.0f,

        // Front-Right face
        0.0f, 0.0f,  0.5f,
        0.5f, 0.0f, -0.5f,
        0.0f, 1.0f,  0.0f,

        // Back face
        0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, -0.5f,
        0.0f, 1.0f,  0.0f
    };
    GenerateObject(pyramid, pyramidVertices, false, false);
    pyramid.shader = new Shader("resources/shaders/test.vs", "resources/shaders/test.fs");


    GenerateCubeData(light, true, false);
    light.shader = new Shader("resources/shaders/light.vs", "resources/shaders/light.fs");
}


//! ----------------------------
//!                            |
//!         INIT WINDOW        |
//!                            |
//!----------------------------|
int Engine::Init(){
    // context.screenWidth = 800.0f;
    // context.screenHeight = 800.0f;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return Errors::GLFW_init_Failed;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Engine::s_window = glfwCreateWindow(context.screenWidth, context.screenHeight, context.title, nullptr, nullptr);
    
    if(!s_window){
        std::cerr << "Failed to Create Window." << std::endl;
        return Errors::Window_Failed;
    }

    Inputs::InitCallBacks(s_window, context.camera);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return Errors::GLAD_Loader_Failed;
    }

    glEnable(GL_DEPTH_TEST);
    ImGuiLayer::Init(s_window);

    OPENGL_INIT();

    return 1;
}


//! ----------------------------
//!                            |
//!              UPDATE        |
//!                            |
//!----------------------------|
void Engine::Update(){}

void Engine::Clean(){
    ImGuiLayer::Shutdown();
    if (s_window) {
        glfwDestroyWindow(s_window);
    }
    delete square.shader;
    delete triangle.shader;
    delete triangle.texture;
    delete cube.shader;
    delete cube.texture;
    glfwTerminate();
    std::cout << "Engine Cleaned Successfully." << std::endl;
}


//! ----------------------------
//!                            |
//!              WINDOW        |
//!                            |
//!----------------------------|
void Engine::CreateWindow(){
    //X ============= INIT OBJECTS ================ //

        //X --- OPENGL OBJECTS VARIABLES --- //

                ObjectValues_DataBase ObjectsDataBase;

                ObjectValues_DataBase proceduralDatabase;

        //X ---------------------------------\\
        
        
        int numCubes = 36;
        float radius = 5.0f;

        for (int i = 0; i < numCubes; i++) {
            float angle = i * (2.0f * 3.14159f / numCubes);
            ObjectValues cube;
            
            // Circular arrangement
            cube.position = glm::vec3(cos(angle) * radius, 0.0f, sin(angle) * radius);
            cube.size = glm::vec3(0.5f);
            cube.color = glm::vec3(sin(angle) * 0.5f + 0.5f, 0.2f, cos(angle) * 0.5f + 0.5f);
            
            proceduralDatabase.cubeList.push_back(cube);
        }

        ObjectValues cubeValues = {
            .color = glm::vec3(1.0f, 1.0f, 1.0f),
            .size = glm::vec3(1.0f, 1.0f, 1.0f),
            .position = glm::vec3(1.0f, 1.0f, 1.0f),
        };
        ObjectValues* sphereValues = nullptr;

        ObjectValues lightValues = {
            .color = { 0.5f, 0.5f, .05f },
            .size = { 1.0f, 1.0f, 1.0f },
            .position = { 0.0f, 3.0f, 0.0f },
        };


        std::vector<Object_c> items = {
            {"Cube", cube, cubeValues},
            {"Light", light, lightValues}
        };
    //X =============================================== \\



    //X ============== IMGUI SETUP =============================== //

        //X --- IMGUI VARIABLES --- //

            ImVec4 clearColor = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

        //X ---------------------------------\\

        // Setup Dear ImGui style
        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        //style.FontSizeBase = 16.0f;
        // style.FrameRounding = 3.0f;
        // style.GrabRounding = 3.0f;

        bool show_demo_window = false;
        // bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        static bool selection[8] = { false, true, false, false, false, false, false};
    //X ========================================================== \\


        
    //X ======================= VARIABLES ==================||
    
    // EMPTY?

    //X ====================================================||

    while(!glfwWindowShouldClose(s_window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Inputs::ProcessInput(s_window, deltaTime);
        Update();

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ImGuiLayer::Begin();

        //X ----------- IMGUI ------ //
        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
        {
            ImGui::Begin("Engine Debug");
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("OpenGL", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("General"))
                {
                    ImGui::Text("This is the Avocado tab!\nblah blah blah blah blah");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Light"))
                {
                    ImGui::SeparatorText("\n Position :");
                    ImGui::SliderFloat("L_P X : ", &lightValues.position.x, -10.0f, 10.0f);
                    ImGui::SliderFloat("L_P Y : ", &lightValues.position.y, -10.0f, 10.0f);
                    ImGui::SliderFloat("L_P Z : ", &lightValues.position.z, -10.0f, 10.0f);

                    ImGui::SeparatorText("\n Color :");
                    ImGui::ColorEdit3("Color", glm::value_ptr(lightValues.color));

                    ImGui::SeparatorText("Size :");
                    ImGui::SliderFloat("L_S X : ", &lightValues.size.x, 0.0f, 5.0f);
                    ImGui::SliderFloat("L_S Y : ", &lightValues.size.y, 0.0f, 5.0f);
                    ImGui::SliderFloat("L_S Z : ", &lightValues.size.z, 0.0f, 5.0f);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Cube"))
                {
                    ImGui::SeparatorText("\n Position :");
                    ImGui::SliderFloat("C_P X : ", &cubeValues.position.x, -10.0f, 10.0f);
                    ImGui::SliderFloat("C_P Y : ", &cubeValues.position.y, -10.0f, 10.0f);
                    ImGui::SliderFloat("C_P Z : ", &cubeValues.position.z, -10.0f, 10.0f);

                    ImGui::SeparatorText("\n Color :");
                    ImGui::ColorEdit3("Color", glm::value_ptr(cubeValues.color));
                    
                    ImGui::SeparatorText("Size :");
                    ImGui::SliderFloat("C_S X : ", &cubeValues.size.x, 0.0f, 5.0f);
                    ImGui::SliderFloat("C_S Y : ", &cubeValues.size.y, 0.0f, 5.0f);
                    ImGui::SliderFloat("C_S Z : ", &cubeValues.size.z, 0.0f, 5.0f);
                    ImGui::EndTabItem();
                }
                ImGui::SeparatorText("\n");
                ImGui::EndTabBar();
            }
            ImGui::Separator();

            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::ColorEdit3("Window Color :", (float*)&clearColor);
            ImGui::Checkbox("Demo Window\n", &show_demo_window);
            ImGui::SeparatorText("OpenGL Options.");
            ImGui::ColorEdit3("Cube Colors :", glm::value_ptr(cubeValues.color));
            ImGui::SliderFloat3("Cube Position :", glm::value_ptr(cubeValues.position), 0.0f, 10.0f);
            ImGui::SliderFloat3("Cube Size :", glm::value_ptr(cubeValues.size), 0.0f, 3.0f);

            if (ImGui::TreeNode("ON/OFF Objects"))
            {
                ImGui::Selectable("1. Triangle", &selection[0]);
                ImGui::Selectable("2. Square", &selection[1]);
                ImGui::Selectable("3. Pyramid", &selection[2]);
                ImGui::Selectable("4. Light", &selection[3]);
                ImGui::Selectable("5. Cube", &selection[4]);
                ImGui::Selectable("6. Sphere", &selection[5]);
                if (ImGui::Selectable("7. N-Cubes", selection[6], ImGuiSelectableFlags_AllowDoubleClick))
                    if (ImGui::IsMouseDoubleClicked(0))
                        selection[6] = !selection[6];
                ImGui::TreePop();
            }

            ImGui::End();
        }
        //X ------------------------------ \\

//! ==================================================================== |

        //X -------- OTHER WORK ---------- //
        glm::mat4 view = context.camera.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.3f));
        projection = glm::perspective(glm::radians(context.camera.Zoom), context.screenWidth / context.screenHeight, 0.1f, 100.0f);


        //* ---------- DRAW TRIANGLE -----
        if(selection[0]){
            triangle.texture->Bind(0);
            triangle.shader->use();
            triangle.shader->setBool("textures", true);
            triangle.shader->setInt("ourTexture", 0);

            triangle.shader->setMat4("view", view);
            triangle.shader->setMat4("projection", projection);

            glm::mat4 triangleModel = glm::mat4(1.0f);
            triangle.shader->setMat4("model", triangleModel);

            glBindVertexArray(triangle.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        }
        //* -------------------------------

        //* --- DRAW YOUR SQUARE ---
        if(selection[1]) {
            square.texture->Bind(0);
            square.shader->use();
            square.shader->setBool("textures", true);
            square.shader->setInt("ourTexture", 0);
            
            square.shader->setMat4("view", view);
            square.shader->setMat4("projection", projection);

            glm::mat4 squareModel = glm::mat4(1.0f);
            squareModel = glm::rotate(squareModel, glm::radians((float)glfwGetTime() * 20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            square.shader->setMat4("model", squareModel);

            glBindVertexArray(square.VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        //* ------------------------

        //* --- DRAW YOUR PYRAMID ---
        if(selection[2])
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        pyramid.shader->use();
        pyramid.shader->setBool("textures", false);
        
        pyramid.shader->setMat4("view", view);
        pyramid.shader->setMat4("projection", projection);

        glm::mat4 pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, glm::vec3(2.0f, 2.0f, 2.0f));
        pyramidModel = glm::rotate(pyramidModel, glm::radians((float)glfwGetTime() * 20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        pyramid.shader->setMat4("model", pyramidModel);

        glBindVertexArray(pyramid.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        //* ------------------------

        //* ----------- Draw Light ------------
        if(selection[3])
        {
            light.shader->use();
        light.shader->setMat4("view", view);
        light.shader->setMat4("projection", projection);

        glm::mat4 lightModel = glm::mat4(1.0f);

        light.shader->setVec3("lightColor", lightValues.color);
        lightModel = glm::translate(lightModel, lightValues.position);
        lightModel = glm::scale(lightModel, lightValues.size);

        light.shader->setMat4("model", lightModel);
        glBindVertexArray(light.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        }
        //* ------------------------------------

        //* ----------- DRAW CUBE TO WORK ON LIGHT ----------
        if(selection[4]){
            cube.texture->Bind(0);
            cube.shader->use();
            cube.shader->setBool("textures", true);
            cube.shader->setInt("ourTexture", 0);
 
            cube.shader->setMat4("view", view);
            cube.shader->setMat4("projection", projection);

            glm::mat4 cubeModel = glm::mat4(1.0f);

            cube.shader->setVec3("lightColor", lightValues.color);
            cube.shader->setVec3("objectColor", cubeValues.color);
            cubeModel = glm::translate(cubeModel, cubeValues.position);
            cubeModel = glm::scale(cubeModel, cubeValues.size);
            
            cube.shader->setMat4("model", cubeModel);

            glBindVertexArray(cube.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
        //* -------------------------------------------------

        //* -------------- DRAW SPHERE --------------------
        if(selection[5]){
            sphere.texture->Bind(0);
        sphere.shader->use();
        sphere.shader->setBool("textures", true);
        sphere.shader->setInt("ourTexture", 0);
        sphere.shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        sphere.shader->setVec3("objectColor", glm::vec3(0.2f, 0.6f, 1.0f));
        sphere.shader->setMat4("view", view);
        sphere.shader->setMat4("projection", projection);

        // Model matrix transformations
        glm::mat4 sphereModel = glm::mat4(1.0f);
        sphereModel = glm::translate(sphereModel, glm::vec3(0.0f, 0.0f, -3.0f));
        sphere.shader->setMat4("model", sphereModel);

        glBindVertexArray(sphere.VAO);
        // Draw using elements (indices size, unsigned int type, offset pointer)
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphere.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        }
        //* ------------------------------------------------

        //* ------ DRAW YOUR N-CUBES ------------------
        if(selection[6]){
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(int i = 0; i < ObjectsDataBase.cubeList.size(); i++) {
            cube.texture->Bind(0);
            cube.shader->use();
            cube.shader->setBool("textures", true);
            cube.shader->setInt("ourTexture", 0);
            cube.shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            
            // Use the color specific to this cube index from your database
            cube.shader->setVec3("objectColor", ObjectsDataBase.cubeList[i].color);
            
            cube.shader->setMat4("view", view);
            cube.shader->setMat4("projection", projection);

            glm::mat4 cubeModel = glm::mat4(1.0f);
            cubeModel = glm::translate(cubeModel, ObjectsDataBase.cubeList[i].position);
            cubeModel = glm::scale(cubeModel, ObjectsDataBase.cubeList[i].size);
            
            // Fixed rotation syntax: added multiplication '*' and wrapped the offset properly
            // cubeModel = glm::rotate(cubeModel, glm::radians((float)glfwGetTime() * 20.0f + (i * 15.0f)), glm::vec3(1.0f, 0.3f, 0.5f));
            
            cube.shader->setMat4("model", cubeModel);

            glBindVertexArray(cube.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal mode
        static float lastSpawnTime = 0.0f;
        if (glfwGetKey(s_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (currentFrame - lastSpawnTime > 0.5f) { // 0.2 second cooldown
                ObjectValues newCube;
                newCube.position = context.camera.Position + context.camera.Front; // Spawn in front of camera
                newCube.size = glm::vec3(0.7f);
                newCube.color = glm::vec3(1.0f, 0.5f, 0.0f);     // Orange color

                ObjectsDataBase.cubeList.push_back(newCube);
                std::cout << "Spawned cube! Total: " << ObjectsDataBase.cubeList.size() << std::endl;

                lastSpawnTime = currentFrame;
            }
        }
        }
        
        //* --------------------------------------------------

        //X ------------------------------ \\

        ImGuiLayer::End();

        glfwSwapBuffers(s_window);
        glfwPollEvents();
    }
}


//! ----------------------------
//!                            |
//!            RUN             |
//!                            |
//!----------------------------|
void Engine::run(){
    Init();

    CreateWindow();

    Clean();
}