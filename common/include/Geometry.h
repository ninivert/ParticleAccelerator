#ifndef GEOMETRY_H
#define GEOMETRY_H

#pragma once

#include <vector>
#include <cmath>
#include <QVector3D>
#include <QQuaternion>
#include "globals.h"
#include "include/Vertex.h"

namespace GEOMETRY {
	typedef std::vector<SimpleVertex> Vertices;

	/****************************************************************
	 * Point (pea)
	 ****************************************************************/

	Vertices const PEA = { SimpleVertex(QVector3D( 0, 0, 0 )) };

	/****************************************************************
	 * Spaghetti (Axes)
	 ****************************************************************/

	Vertices const SPAGHETTI = {
		SimpleVertex(QVector3D( 0, 0, 0 )),
		SimpleVertex(QVector3D( 1, 0, 0 ))
	};

	/****************************************************************
	 * Pancake (Disk)
	 ****************************************************************/

	static Vertices getDiskVertices() {
		Vertices vertices;
		double step(2*M_PI/GRAPHICS::PRECISION);
		QVector3D n(0, 1, 0);

		for (size_t i(0); i < GRAPHICS::PRECISION; ++i) {
			double angle(step * i);
			QVector3D position(std::cos(angle), 0, std::sin(angle));
			vertices.push_back(SimpleVertex(position, n));
		}

		return vertices;
	}

	Vertices const PANCAKE(getDiskVertices());

	/****************************************************************
	 * Penne (cylinder)
	 ****************************************************************/

	// Penne is oriented along the x-axis

	static Vertices getCyclinderVertices() {
		Vertices vertices;
		double step(2*M_PI/GRAPHICS::PRECISION);

		for (size_t i(0); i < GRAPHICS::PRECISION; ++i) {
			double angle1(step * i), angle2(step * (i + 1));
			double x1(std::cos(angle1)), x2(std::cos(angle2)), y1(std::sin(angle1)), y2(std::sin(angle2));

			// Inside
			// vertices.push_back(SimpleVertex(QVector3D(-0.5, x1, y1)));
			// vertices.push_back(SimpleVertex(QVector3D(0.5, x1, y1)));
			// vertices.push_back(SimpleVertex(QVector3D(0.5, x2, y2)));
			// vertices.push_back(SimpleVertex(QVector3D(-0.5, x1, y1)));
			// vertices.push_back(SimpleVertex(QVector3D(0.5, x2, y2)));
			// vertices.push_back(SimpleVertex(QVector3D(-0.5, x2, y2)));

			// Vertices
			QVector3D v1(-0.5, x1, y1);
			QVector3D v2(0.5, x2, y2);
			QVector3D v3(0.5, x1, y1);
			QVector3D v4(-0.5, x1, y1);
			QVector3D v5(-0.5, x2, y2);
			QVector3D v6(0.5, x2, y2);

			// Edges
			QVector3D e1(v2 - v1);
			QVector3D e2(v3 - v2);

			// Normal
			QVector3D n(QVector3D::crossProduct(e1, e2));

			// Outside
			vertices.push_back(SimpleVertex(v1, n));
			vertices.push_back(SimpleVertex(v2, n));
			vertices.push_back(SimpleVertex(v3, n));
			vertices.push_back(SimpleVertex(v4, n));
			vertices.push_back(SimpleVertex(v5, n));
			vertices.push_back(SimpleVertex(v6, n));
		}

		return vertices;
	}

	Vertices const PENNE(getCyclinderVertices());

	/****************************************************************
	 * Macaroni (torus)
	 ****************************************************************/

	static Vertices getTorusVertices(double radius, double angle) {
		Vertices vertices;
		double stepI(angle / GRAPHICS::PRECISION);
		double stepJ(2*M_PI / GRAPHICS::PRECISION);

		QVector3D const up(0, 1, 0);
		QQuaternion const smallRot(QQuaternion::fromAxisAndAngle(up, stepI * 180 / M_PI));

		for (size_t i(0); i < GRAPHICS::PRECISION; ++i) {
			double alpha(stepI * i);
			QQuaternion bigRot(QQuaternion::fromAxisAndAngle(up, alpha * 180 / M_PI));

			for (size_t j(0); j < GRAPHICS::PRECISION; ++j) {
				double beta1(stepJ * j), beta2(stepJ * (j + 1));
				QVector3D pos11(1 + std::cos(beta1) * radius, std::sin(beta1) * radius, 0);
				QVector3D pos12(1 + std::cos(beta2) * radius, std::sin(beta2) * radius, 0);
				pos11 = bigRot * pos11;
				pos12 = bigRot * pos12;
				QVector3D pos21 = smallRot * pos11;
				QVector3D pos22 = smallRot * pos12;

				// Edges
				QVector3D e1(pos21 - pos11);
				QVector3D e2(pos22 - pos21);

				// Normal
				QVector3D n(QVector3D::crossProduct(e1, e2));

				// Inside
				// vertices.push_back(SimpleVertex(pos11));
				// vertices.push_back(SimpleVertex(pos22));
				// vertices.push_back(SimpleVertex(pos21));
				// vertices.push_back(SimpleVertex(pos11));
				// vertices.push_back(SimpleVertex(pos12));
				// vertices.push_back(SimpleVertex(pos22));

				// Outside
				vertices.push_back(SimpleVertex(pos11, n));
				vertices.push_back(SimpleVertex(pos21, n));
				vertices.push_back(SimpleVertex(pos22, n));
				vertices.push_back(SimpleVertex(pos11, n));
				vertices.push_back(SimpleVertex(pos22, n));
				vertices.push_back(SimpleVertex(pos12, n));
			}
		}

		return vertices;
	}

	Vertices const MACARONI(getTorusVertices(0.1, M_PI*2));

	/****************************************************************
	 * Cube
	 * TODO: define normal vectors
	 ****************************************************************/

	// Front Vertices
	#define VERTEX_FTR SimpleVertex(QVector3D( 0.5,  0.5,  0.5))
	#define VERTEX_FTL SimpleVertex(QVector3D(-0.5,  0.5,  0.5))
	#define VERTEX_FBL SimpleVertex(QVector3D(-0.5, -0.5,  0.5))
	#define VERTEX_FBR SimpleVertex(QVector3D( 0.5, -0.5,  0.5))

	// Back Vertices
	#define VERTEX_BTR SimpleVertex(QVector3D( 0.5,  0.5, -0.5))
	#define VERTEX_BTL SimpleVertex(QVector3D(-0.5,  0.5, -0.5))
	#define VERTEX_BBL SimpleVertex(QVector3D(-0.5, -0.5, -0.5))
	#define VERTEX_BBR SimpleVertex(QVector3D( 0.5, -0.5, -0.5))

	Vertices const CUBE = {
		// Face 1 (Front)
		VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
		VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
		// Face 2 (Back)
		VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
		VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
		// Face 3 (Top)
		VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
		VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
		// Face 4 (Bottom)
		VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
		VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
		// Face 5 (Left)
		VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
		VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
		// Face 6 (Right)
		VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
		VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
	};

	#undef VERTEX_BBR
	#undef VERTEX_BBL
	#undef VERTEX_BTL
	#undef VERTEX_BTR

	#undef VERTEX_FBR
	#undef VERTEX_FBL
	#undef VERTEX_FTL
	#undef VERTEX_FTR
}

#endif
