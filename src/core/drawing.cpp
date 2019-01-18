#include "drawing.h"

Drawing drawing;

double Drawing::convertColorFloatToRGB(int rgbValue) {
	return (double)rgbValue / 255;
}

double Drawing::convertColorFloatToRGB(double rgbValue) {
	return (double)rgbValue / 255;
}

void Drawing::drawText(const char* message, Vector2 position, int size) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glEnable(GL_TEXTURE_2D);

	SDL_Color color;
	color.r = 0; color.g = 0; color.b = 0; color.a = 255;
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (font == nullptr) {
		 font = TTF_OpenFont("res/Aller_Rg.ttf", size);
	}

	SDL_Surface *sFont = TTF_RenderText_Blended(font, message, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

	int width, height;
	TTF_SizeText(font, message, &width, &height);

	glBegin(GL_QUADS);
	for (int x = 0; x < 4; x++) {
		glTexCoord2d(vectors[x].x, vectors[x].y);

		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Drawing::drawText(const char* message, Vector2 position, int size, SDL_Color color) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glEnable(GL_TEXTURE_2D);
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (font == nullptr) {
		 font = TTF_OpenFont("res/Aller_Rg.ttf", size);
	}

	SDL_Surface *sFont = TTF_RenderText_Blended(font, message, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

	int width, height;
	TTF_SizeText(font, message, &width, &height);

	glBegin(GL_QUADS);
	for (int x = 0; x < 4; x++) {
		glTexCoord2d(vectors[x].x, vectors[x].y);

		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Drawing::drawPoint(Vector2 position) {
	glBegin(GL_POINTS);
	glColor4f(1, 1, 1, 1);
	glVertex2d(position.x - (configuration.getScreenWidth() / 2), position.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawPoint(Vector2 position, int alpha) {
	glBegin(GL_POINTS);
	glColor4f(1, 1, 1, convertColorFloatToRGB(alpha));
	glVertex2d(position.x - (configuration.getScreenWidth() / 2), position.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawPoint(Vector2 position, int color[3]) {
	glBegin(GL_POINTS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	glVertex2d(position.x - (configuration.getScreenWidth() / 2), position.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawPoint(Vector2 position, int color[3], int alpha) {
	glBegin(GL_POINTS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	glVertex2d(position.x - (configuration.getScreenWidth() / 2), position.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawRectOutline(Vector2 position, int width, int height, double angle) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_POINTS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void Drawing::drawRect(Vector2 position, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void Drawing::drawRect(Vector2 position, int width, int height, double angle) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void Drawing::drawRect(Vector2 position, int width, int height, double angle, int color[3]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void Drawing::drawRect(Vector2 position, int width, int height, double angle, int color[3], int alpha) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void Drawing::drawRect(Vector2 position, int width, int height, int color[3]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void Drawing::drawRect(Vector2 position, int width, int height, int color[3], int alpha) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void Drawing::drawRect(Vector2 position, int width, int height, int color[3], double alpha) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void Drawing::drawLine(Vector2 a, Vector2 b) {
	glBegin(GL_LINES);
	glColor4f(1, 1, 1, 1);
	glVertex2f(a.x - (configuration.getScreenWidth() / 2), a.y - (configuration.getScreenHeight() / 2));
	glVertex2f(b.x - (configuration.getScreenWidth() / 2), b.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawLine(Vector2 a, Vector2 b, int color[3]) {
	glBegin(GL_LINES);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	glVertex2f(a.x - (configuration.getScreenWidth() / 2), a.y - (configuration.getScreenHeight() / 2));
	glVertex2f(b.x - (configuration.getScreenWidth() / 2), b.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawLine(Vector2 a, Vector2 b, int color[3], int alpha) {
	glBegin(GL_LINES);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	glVertex2f(a.x - (configuration.getScreenWidth() / 2), a.y - (configuration.getScreenHeight() / 2));
	glVertex2f(b.x - (configuration.getScreenWidth() / 2), b.y - (configuration.getScreenHeight() / 2));
	glEnd();
}

void Drawing::drawLine(Vector2 position, int width, int thickness, int color[3], double angle) {
	Vector2 vectors[2]{
		Vector2(-1, 0),
		Vector2(1, 0)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x - (configuration.getScreenWidth() / 2), position.y - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x - (configuration.getScreenWidth() / 2)), -(position.y - (configuration.getScreenHeight() / 2)), 0);
	
	glBegin(GL_LINES);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(thickness);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < 2; x++) {
		vectors[x].x *= width;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void Drawing::drawLineStrip(Vector2 *points, int count, Vector2 position, float scale, int color[3]) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < count; x++) { glVertex2f((points[x].x * scale) + position.x - (configuration.getScreenWidth() / 2), (points[x].y * scale) + position.y - (configuration.getScreenHeight() / 2)); }
	glEnd();
};

void Drawing::drawLineStrip(std::vector<Vector2> points, int color[3]) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (configuration.getScreenWidth() / 2), points[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawLineStrip(std::vector<Vector2> points, int color[3], int alpha) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (configuration.getScreenWidth() / 2), points[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawLineStrip(std::vector<Vector2> points, int offset, int color[3], int alpha) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (configuration.getScreenWidth() / 2), offset + points[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawLineStrip(std::vector<Vector2> points, std::vector<Vector2> pointsB, int color[3]) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < points.size(); x++) { glVertex2f(((points[x].x + pointsB[x].x) / 2) - (configuration.getScreenWidth() / 2), ((points[x].y + pointsB[x].y) / 2) - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawLineStrip(std::vector<Vector2> points, std::vector<Vector2> pointsB, int offset, int color[3], int alpha) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < points.size(); x++) { glVertex2f(((points[x].x + pointsB[x].x) / 2) - (configuration.getScreenWidth() / 2), offset + ((points[x].y + pointsB[x].y) / 2) - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawLineStrip(Vector2 position, double width, double height, std::vector<Vector2> vertices, double angle, int color[3]) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < vertices.size(); x++) { 
		glVertex2f(position.x + vertices[x].x - (configuration.getScreenWidth() / 2), position.y + vertices[x].y - (configuration.getScreenHeight() / 2)); 
	}
	glVertex2f(position.x + vertices[0].x - (configuration.getScreenWidth() / 2), position.y + vertices[0].y - (configuration.getScreenHeight() / 2));
	glEnd();
	glPopMatrix();
}

void Drawing::drawPolygon(std::vector<Vector2> points, int color, int alpha) {
	glBegin(GL_POLYGON);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color), convertColorFloatToRGB(color), convertColorFloatToRGB(color), convertColorFloatToRGB(alpha));
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (configuration.getScreenWidth() / 2), points[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawPolygon(std::vector<Vector2> points, int color[3], int alpha) {
	glBegin(GL_POLYGON);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (configuration.getScreenWidth() / 2), points[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawPolygon(Vector2 position, std::vector<Vector2> vertices, int color[3], int alpha) {
	glBegin(GL_POLYGON);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < vertices.size(); x++) { 
		glVertex2f(position.x + vertices[x].x - (configuration.getScreenWidth() / 2), position.y + vertices[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
}

void Drawing::drawPolygon(Vector2 position, double width, double height, std::vector<Vector2> vertices, double angle, int color[3], int alpha) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_POLYGON);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), convertColorFloatToRGB(alpha));
	for (int x = 0; x < vertices.size(); x++) { 
		glVertex2f(position.x + vertices[x].x - (configuration.getScreenWidth() / 2), position.y + vertices[x].y - (configuration.getScreenHeight() / 2)); }
	glEnd();
	glPopMatrix();
}

void Drawing::drawCircle(Vector2 position, float radius) {
	glBegin(GL_LINE_LOOP);
	glColor4f(1, 1, 1, 1);

	double radians = PI / 180;
	for (int i = 0; i < 360; i++) {
		glVertex2d((cos(i * radians)*radius) - (configuration.getScreenWidth() / 2) + position.x, (sin(i * radians)*radius) - (configuration.getScreenHeight() / 2) + position.y);
	}

	glEnd();
}

void Drawing::drawCircle(Vector2 position, float radius, int color[3]) {
	glBegin(GL_LINE_LOOP);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);

	double radians = PI / 180;
	for (int i = 0; i < 360; i++) {
		glVertex2d((cos(i * radians)*radius) - (configuration.getScreenWidth() / 2) + position.x, (sin(i * radians)*radius) - (configuration.getScreenHeight() / 2) + position.y);
	}

	glEnd();
}

void Drawing::drawCircleFill(Vector2 position, float radius, int color[3]) {
	glBegin(GL_LINE_LOOP);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);

	double radians = PI / 180;
	for (int r = radius; r >= 0; r--) {
		for (int i = 0; i < 360; i++) {
			glVertex2d((cos(i * radians)*r) - (configuration.getScreenWidth() / 2) + position.x, (sin(i * radians)*r) - (configuration.getScreenHeight() / 2) + position.y);
		}
	}

	glEnd();
}

void Drawing::drawTriangle(Vector2 position, int width, int height) {
	Vector2 vectors[3]{
		Vector2(0, 0),
		Vector2(.5, 1),
		Vector2(1, 0),
	};

	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 3; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void Drawing::drawTriangle(Vector2 position, int width, int height, double angle) {
	Vector2 vectors[3]{
		Vector2(0, 1),
		Vector2(1, .5),
		Vector2(0, 0),
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (configuration.getScreenWidth() / 2), position.y + (height / 2) - (configuration.getScreenHeight() / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (configuration.getScreenWidth() / 2)), -(position.y + (height / 2) - (configuration.getScreenHeight() / 2)), 0);
	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 3; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}