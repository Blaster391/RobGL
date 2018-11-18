#pragma once
#include "PostProcessingFX.h"
#include "Text.h"
namespace rgl {
	class UITextFX : public PostProcessingFX
	{
	public:
		UITextFX(std::vector<Shader*> shaders, Text* alphabet);
		void setText(std::string text);
		void setPosition(float x, float y);
		void setScale(float scale);
		void setColour(glm::vec4 colour);
		~UITextFX();

		virtual void process(float delta, GLuint& displayTex, GLuint& processTex) override;
	private:
		std::string _text;
		float _xPos;
		float _yPos;
		float _scale;
		glm::vec4 _colour;
		Text* _alphabet;

		//Returns position of the origin of the next character
		int drawCharacter(char c, int xOrigin);
	};

}

