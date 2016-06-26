#ifndef ENGINE_I_RENDER_TARGET_H
#define ENGINE_I_RENDER_TARGET_H
class IRenderTarget
{
public:
	virtual void BindAsRenderTarget() = 0;
};
#endif // !ENGINE_I_RENDER_TARGET_H
