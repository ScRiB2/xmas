#ifndef MODEL_3D_H 
#define MODEL_3D_H
#include <string>
#include "Matrix.h"
#include "AffineTransform.h"

class Model3D {
private:
	Matrix<> CumulativeAT;
	Matrix<> Vertices;
	Matrix<> InitialVertices;
	Matrix<> ProjectedVertices;
	Matrix<int> Faces;
	Matrix<int> Edges;
public:
	Model3D() : Vertices(), Edges() {}
	Model3D(const Matrix<> Vertices, const Matrix<int> Edges) :Vertices(Vertices), Edges(Edges),
		CumulativeAT(Identify()), InitialVertices(Vertices) {}
	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
	
	double GetVertexX(int number) {
		return ProjectedVertices(number, 1)/ ProjectedVertices(number, 3);
	}
	double GetVertexY(int number) {
		return ProjectedVertices(number, 2) / ProjectedVertices(number, 3);
	}

	void Apply(Matrix<> transform)
	{
		CumulativeAT = transform * CumulativeAT;
		Vertices = InitialVertices * CumulativeAT.transpos();
	}

	void Project() {
		double P[12] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 1
		};
		Matrix<> ProjectedMatrix = Matrix<>(3, 4, P);
		ProjectedVertices = Vertices * ProjectedMatrix.transpos();
	}

	Matrix<int> GetFaces() { return Faces; }
};

#endif MODEL_3D_H
