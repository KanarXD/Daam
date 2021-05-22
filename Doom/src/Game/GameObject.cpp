#include "pch.h"
#include "GameObject.h"
#include "Renderer/Renderer.h"
#include "Renderer/Library/ModelsLibrary.h"

GameObject::GameObject(const Transform& transform, const std::string& type)
	: transform(transform), type(type), timer(0.0) 
{
	if (GOModels.find(type) != GOModels.end())
	{
		hitbox = GOModels.at(type).hitbox;
		modelPath = GOModels.at(type).modelPath;
	}
}

void GameObject::Update(float dt)
{
	timer += dt;
}

void GameObject::Draw()
{
	if (modelPath != "")
	{
		std::optional<const Model*> model = ModelsLibrary::GetInstance()->Get(modelPath);
		if (!model.has_value())
		{
			LOGERROR("GameObject - ModelsLibrary::Get(...) - ", modelPath);
			return;
		}

		Renderer::DrawModel(*model.value(), 
			glm::scale(glm::translate(glm::mat4(1.0f), transform.position), transform.scale));
	}

	if (Hitbox::showHitbox)
	{
		std::optional<const Model*> model;
		if (hitbox.useRound)
			model = ModelsLibrary::GetInstance()->Get(hitbox.rdModelPath);
		else
			model = ModelsLibrary::GetInstance()->Get(hitbox.sqModelPath);
		if (!model.has_value())
		{
			LOGERROR("GameObject - ModelsLibrary::Get(...) - ", (hitbox.useRound)? hitbox.rdModelPath : hitbox.sqModelPath);
			return;
		}

		Renderer::DrawModel(*model.value(), 
			glm::scale(glm::translate(glm::mat4(1.0f), transform.position + hitbox.offset), transform.scale * hitbox.scaleModifier));
	}
}
