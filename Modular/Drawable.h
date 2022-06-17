#pragma once
#include "Graphics.h"
#include <DirectXMath.h>

class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);
	void DrawDefault(Graphics& gfx) const noexcept(!IS_DEBUG);
	void SetCount(UINT count) noexcept;
	virtual void Update(float dt) noexcept = 0;
	virtual ~Drawable() = default;
protected:
	void AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept(!IS_DEBUG);
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
private:
	const class IndexBuffer* pIndexBuffer = nullptr;
	UINT count;
	std::vector<std::unique_ptr<Bindable>> binds;
};