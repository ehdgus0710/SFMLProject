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
	virtual bool Save() const = 0;
	virtual bool Load() = 0;
public:
	Entity() {}
	virtual ~Entity() {}
};

