#include "FontRenderer.h"

void FontRenderer::init()
{
	FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "[Error] FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "resources/Arial.ttf", 0, &face))
    {
        std::cout << "[Error] FREETYPE: Failed to load font" << std::endl;
        return;
    }

    setupShaders();
    glUseProgram(programId);

    FT_Set_Pixel_Sizes(face, 0, 1024);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 32; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "[Error] FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            { (int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows},
            { (int)face->glyph->bitmap_left, (int)face->glyph->bitmap_top},
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        charactersMap.insert(std::pair<char, Character>(c, character));
    }
    
    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glGenBuffers(1, &VBO));
        GLCALL(glBindVertexArray(VAO));
            GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
                GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
                GLCALL(glEnableVertexAttribArray(0));
                
                GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
        GLCALL(glBindVertexArray(NULL));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, NULL));
    GLCALL(glUseProgram(NULL));

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void FontRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color, glm::vec3 rotation)
{
    glUseProgram(programId);
    glm::mat4 projection = glm::ortho<float>(0, windowWidth, 0, windowHeight);
    GLCALL(glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection)));
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    GLCALL(glUniformMatrix4fv(rotationLocation, 1, GL_FALSE, glm::value_ptr(transform)));
    
    GLCALL(glUniform3f(textColourLocation, color.x, color.y, color.z));
    GLCALL(glActiveTexture(GL_TEXTURE0));
    GLCALL(glBindVertexArray(VAO));

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = charactersMap[*c];

        float xpos = x + ch.Bearing[0] * scale;
        float ypos = y - (ch.Size[1] - ch.Bearing[1]) * scale;

        float w = ch.Size[0] * scale;
        float h = ch.Size[1] * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        GLCALL(glBindTexture(GL_TEXTURE_2D, ch.TextureID));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
            GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, NULL));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));
        // now advance cursors to the next glyph 
        // bitshift by 6 to get value in pixels (2^6 = 64)
        x += (ch.Advance >> 6) * scale; 
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(NULL);

}

void FontRenderer::setupShaders()
{
    programId = glCreateProgram();

    std::string vertexShaderSource = utils::readFile("resources/shaders/font_vertex_shader.glsl");
    std::string fragmentShaderSource = utils::readFile("resources/shaders/font_fragment_shader.glsl");

    const char* shaderSource = vertexShaderSource.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderSource, nullptr);
    glCompileShader(vertexShader);
    int success = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "[ERROR] Could not compile vertex shader in Model Renderer!" << std::endl;
        utils::printShaderError(vertexShader);
        return;
    }

    glAttachShader(programId, vertexShader);

    // Fragment Shader
    shaderSource = fragmentShaderSource.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char**)&shaderSource, nullptr);
    glCompileShader(fragmentShader);
    success = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "[ERROR] Could not compile fragment shader in Model Renderer!" << std::endl;
        utils::printShaderError(fragmentShader);
        return;
    }
    glAttachShader(programId, fragmentShader);

    // Some code to link, compile and validate you shaders 
    glLinkProgram(programId);
    success = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        std::cerr << "[ERROR] Could not link shader in Model Renderer! \n" << std::endl;
        return;
    }

    glValidateProgram(programId);
    success = GL_FALSE;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
    if (success != GL_TRUE) {
        std::cerr << "[ERROR] Could not validate shader in Model Renderer! \n" << std::endl;
        return;
    }
    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLCALL(glUseProgram(programId));


    textLocation = glGetUniformLocation(programId, "text");
    projectionLocation = glGetUniformLocation(programId, "projection");
    rotationLocation = glGetUniformLocation(programId, "rotation");
    textColourLocation = glGetUniformLocation(programId, "textColour");

    GLCALL(glUseProgram(NULL));

}
