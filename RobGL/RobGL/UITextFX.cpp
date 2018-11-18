#include "UITextFX.h"

namespace rgl {
	UITextFX::UITextFX(std::vector<Shader*> shaders, Text* alphabet) : PostProcessingFX(shaders,1),  _alphabet(alphabet)
	{
	}
	void UITextFX::setText(std::string text)
	{
		_text = text;
	}
	void UITextFX::setPosition(float x, float y)
	{
		_xPos = x;
		_yPos = y;
	}
	void UITextFX::setScale(float scale)
	{
		_scale = scale;
	}
	void UITextFX::setColour(glm::vec4 colour)
	{
		_colour = colour;
	}
	UITextFX::~UITextFX()
	{
	}

	void UITextFX::process(float delta, GLuint & displayTex, GLuint & processTex)
	{
		if (!beginDraw()) {
			return;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, processTex, 0);

		glUniform3f(glGetUniformLocation(_program, "textColor"), _colour.x, _colour.y, _colour.z);
		glActiveTexture(GL_TEXTURE0);

		int xOrigin = 0;
		for (auto& c : _text) {
			xOrigin = drawCharacter(c, xOrigin);
		}

		GLuint temp = processTex;
		processTex = displayTex;
		displayTex = temp;

		endDraw();
	}

	int UITextFX::drawCharacter(char c, int xOrigin)
	{
		Character ch = _alphabet->getCharacter(c);

		float xpos = _xPos + xOrigin + ch.Bearing.x * _scale;
		float ypos = _yPos - (ch.Size.y - ch.Bearing.y) * _scale;

		float w = ch.Size.x * _scale;
		float h = ch.Size.y * _scale;

		//Screen space model matrix
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(xpos, ypos, 0)) * glm::scale(glm::mat4(1), glm::vec3(w,h,1) * 0.01f);

		_quadObject->setModelMatrix(modelMatrix);

		_quadTexture->setPointer(ch.TextureID);

		// Update VBO for each character
		//GLfloat vertices[6][4] = {
		//	{ xpos,     ypos + h,   0.0, 0.0 },
		//	{ xpos,     ypos,       0.0, 1.0 },
		//	{ xpos + w, ypos,       1.0, 1.0 },

		//	{ xpos,     ypos + h,   0.0, 0.0 },
		//	{ xpos + w, ypos,       1.0, 1.0 },
		//	{ xpos + w, ypos + h,   1.0, 0.0 }
		//};
		//// Render glyph texture over quad
		//glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		_quadObject->draw(0,_program);


		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		return xOrigin + (ch.Advance >> 6) * _scale; // Bitshift by 6 to get value in pixels (2^6 = 64)




	}

}

