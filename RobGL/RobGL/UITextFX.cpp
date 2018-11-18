#include "UITextFX.h"

namespace rgl {
	UITextFX::UITextFX(std::vector<Shader*>& shaders, Text* alphabet) : PostProcessingFX(shaders,1),  _alphabet(alphabet)
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

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, displayTex, 0);

		glUniform3f(glGetUniformLocation(_program, "textColor"), _colour.x, _colour.y, _colour.z);
		glActiveTexture(GL_TEXTURE0);

		float xOrigin = 0;
		for (auto& c : _text) {
			xOrigin = drawCharacter(c, xOrigin);
		}

		endDraw();
	}

	float UITextFX::drawCharacter(char c, float xOrigin)
	{
		Character ch = _alphabet->getCharacter(c);

		float xpos = -1 + _xPos + xOrigin;
		float ypos = _yPos;

		float w = ch.Size.x * _scale;
		float h = ch.Size.y * _scale;

		//Screen space model matrix
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(xpos, ypos, 0)) * glm::scale(glm::mat4(1), glm::vec3(w,h,1) * 0.01f);

		_quadObject->setModelMatrix(modelMatrix);

		_quadTexture->setPointer(ch.TextureID);


		_quadObject->draw(0,_program);


		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		return xOrigin + (ch.Advance * (1.0/64.0f) * (1.0/200)); // Bitshift by 6 to get value in pixels (2^6 = 64)




	}

}

