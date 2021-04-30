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
    if (FT_New_Face(ft, "resources/arial.ttf", 0, &face))
    {
        std::cout << "[Error] FREETYPE: Failed to load font" << std::endl;
        return;
    }

    setupShaders();
    //glUseProgram(programId);

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
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
    
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
        //glBindVertexArray(VAO);
            //glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
                glEnableVertexAttribArray(0);
                
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glUseProgram(NULL);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void FontRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    //glm::mat4 projection = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight));
    //GLCALL(glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection)));
    
    glActiveTexture(GL_TEXTURE0);
    //glBindVertexArray(VAO);

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
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
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


}
