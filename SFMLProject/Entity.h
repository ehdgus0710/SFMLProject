#pragma once

class Entity
{
public:
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void LateUpdate() {}
	virtual void Awake() {}
	virtual void Start() {}
public:
	Entity() {}
	virtual ~Entity() {}
};

