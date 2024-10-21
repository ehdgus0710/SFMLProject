#pragma once

class Entity
{
public:
	virtual void Update(const float& deltaTime) {}
	virtual void FixedUpdate(const float& deltaTime) {}
	virtual void LateUpdate(const float& deltaTime) {}
	virtual void Awake() {}
	virtual void Start() {}

public:
	virtual bool Save() const = 0;
	virtual bool Load() = 0;
public:
	Entity() {}
	virtual ~Entity() {}
};

