#pragma once
#include "Drawable.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "IndexBuffer.h"
#include "StringConverter.h"
#include "Vertex.h"
#include "Topology.h"
#include "TransformCbuf.h"

class Sprite : public Drawable
{
public:
	Sprite(float x, float y, Graphics& gfx, std::string fileName);
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	~Sprite() = default;
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	float x;
	float y;
	std::string assetName;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> spriteTexture;
};