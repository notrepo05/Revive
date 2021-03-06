#pragma once

#include "CompositorBase.h"

#include <GL/glew.h>
#include <openvr.h>

class CompositorGL :
	public CompositorBase
{
public:
	CompositorGL();
	virtual ~CompositorGL();

	static CompositorGL* Create();
	virtual vr::EGraphicsAPIConvention GetAPI() { return vr::API_OpenGL; };
	virtual void OnSubmitComplete() { }

	// Texture Swapchain
	virtual ovrResult CreateTextureSwapChain(const ovrTextureSwapChainDesc* desc, ovrTextureSwapChain* out_TextureSwapChain);
	virtual void DestroyTextureSwapChain(ovrTextureSwapChain chain);
	virtual void RenderTextureSwapChain(ovrTextureSwapChain chain, vr::EVREye eye, vr::VRTextureBounds_t bounds, vr::HmdVector4_t quad);

	// Mirror Texture
	virtual ovrResult CreateMirrorTexture(const ovrMirrorTextureDesc* desc, ovrMirrorTexture* out_MirrorTexture);
	virtual void DestroyMirrorTexture(ovrMirrorTexture mirrorTexture);
	virtual void RenderMirrorTexture(ovrMirrorTexture mirrorTexture);

protected:
	static GLenum TextureFormatToInternalFormat(ovrTextureFormat format);
	static GLenum TextureFormatToGLFormat(ovrTextureFormat format);
	static GLboolean glewInitialized;

	GLuint CreateTexture(GLsizei Width, GLsizei Height, ovrTextureFormat Format);
	GLuint CreateFramebuffer(GLuint texture);

	GLuint m_CompositorTargets[ovrEye_Count];
	vr::glUInt_t m_MirrorTextures[ovrEye_Count];
	vr::glSharedTextureHandle_t m_MirrorHandles[ovrEye_Count];

private:
	static void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};
