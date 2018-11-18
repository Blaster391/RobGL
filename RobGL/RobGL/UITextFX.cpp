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



		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, processTex, 0);

		glUniform3f(glGetUniformLocation(_program, "textColor"), _colour.x, _colour.y, _colour.z);
		glActiveTexture(GL_TEXTURE0);

		glUniform1i(glGetUniformLocation(_program, "textTex"), 2);
	

		_quadTexture->setPointer(displayTex);

		float xOrigin = 0;
		for (auto& c : _text) {
			xOrigin = drawCharacter(c, xOrigin);
		}



		GLuint temp = processTex;
		processTex = displayTex;
		displayTex = temp;

		endDraw();
	}

	float UITextFX::drawCharacter(char c, float xOrigin)
	{
		Character ch = _alphabet->getCharacter(c);

		float xpos = _xPos + xOrigin;
		float ypos = _yPos - (ch.Size.y - ch.Bearing.y) * _scale;

		ypos = _yPos;

		float w = ch.Size.x * _scale;
		float h = ch.Size.y * _scale;

		//Screen space model matrix
		//glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(xpos, ypos, 0)) * glm::scale(glm::mat4(1), glm::vec3(w,h,1) * 0.01f);

	//	_quadObject->setModelMatrix(modelMatrix);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glActiveTexture(GL_TEXTURE0);

		glUniform1f(glGetUniformLocation(_program, "textHeight"), h);
		glUniform1f(glGetUniformLocation(_program, "textWidth"), w);

		glUniform1f(glGetUniformLocation(_program, "textScale"), w);

		glUniform1f(glGetUniformLocation(_program, "xpos"), xpos);
		glUniform1f(glGetUniformLocation(_program, "ypos"), ypos);

		_quadObject->draw(0,_program);


		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		return xOrigin + (ch.Advance); // Bitshift by 6 to get value in pixels (2^6 = 64)




	}

}

