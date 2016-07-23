#include "render_visitor.h"
#include "mesh.h"

void RenderVisitor::Apply(Mesh & mesh)
{
	mesh.Draw();
}
