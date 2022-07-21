#include "Sprite.h"
#include "VertexBuffer.h"
#include "Macros.h"

Sprite::Sprite(float x, float y, Graphics& gfx, std::string fileName)
	:
	x(x),
	y(y),
	assetName(fileName)
{
	std::vector < Vertex2D > vertices =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{-0.5f, 0.5f, 0.0f, 0.0f },
		{0.5f, 0.5f, 1.0f, 0.0f},

		{-0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f,   0.5f, 1.0f, 0.0f},
		{0.5f,  -0.5f, 1.0f, 1.0f},
	};

	SetCount((UINT)std::size(vertices));

	spriteTexture = gfx.LoadTexture(assetName);

	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

	std::string vert = cwd;
	vert += "TextureVS.cso";

	auto vs = std::make_unique<VertexShader>(gfx, StringConverter::StringToWide(vert));
	auto vsbc = vs->GetBytecode();
	AddBind(std::move(vs));

	std::string ps = cwd;
	ps += "TexturePS.cso";

	AddBind(std::make_unique<PixelShader>(gfx, StringConverter::StringToWide(ps)));

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};

	gfx.SetPixelShaderResource(0, 1, this->spriteTexture);

	AddBind(std::make_unique<InputLayout>(gfx, layout, vsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
}

void Sprite::Update(float dt) noexcept
{
}

DirectX::XMMATRIX Sprite::GetTransformXM() const noexcept
{
	return DirectX::XMMATRIX();
}
