#ifndef PAINT_APP_H
#define PAINT_APP_H

#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

struct Color {
    float r;
    float g;
    float b;

    Color() {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void colorSelect(Color newColor) {
        this->r = newColor.r;
        this->g = newColor.g;
        this->b = newColor.b;
    }

    void setRed() {   // COLOR: RED
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    void setGreen() {  // COLOR: GREEN
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
    }

    void setBlue() {  // COLOR: BLUE
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
    }
};
struct Button {
    std::string text;
    float x;
    float y;
    float w;
    float h;
    bool buttonPressed;

    Button() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        text = "Button";
        buttonPressed = false;
    }

    Button(std::string text, float x, float y) {
        this->text = text;
        this->x = x;
        this->y = y;
        w = 0.4f;
        h = 0.2f;
        buttonPressed = false;
    }

    void draw() {
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float paintPadding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + paintPadding;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

            glVertex2f(x, y - h);
            glVertex2f(x, y);
        glEnd();

        if (buttonPressed) {
            glRasterPos2f(x + (paintPadding / 2) - 0.01, y - (h / 2) - 0.045);
        } else {
            glRasterPos2f(x + (paintPadding / 2), y - (h / 2) - 0.025);
        }
        
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }
    }

    bool isClicked(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};
struct Circle {
    float x;
    float y;
    Color color;
    float stroke;
    bool selected;

    Circle() {
        x = 0.0f;
        y = 0.0f;
        stroke = 10.0f;
        selected = false;
    }

    Circle(float x, float y, float stroke, Color color) {
        this->x = x;
        this->y = y;
        this->color = color;
        this->stroke = stroke;
        this->selected = false;
    }

    void draw() {
        glColor3f(color.r, color.g, color.b);
        glPointSize(stroke);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();

        if(selected){
            Circle outer(x,y, stroke-3.0, Color(1.0f, 1.0f, 1.0f));
            Circle inner(x,y, stroke-8.0, color);
            outer.draw();
            inner.draw();
        }
    }

    bool isClicked(float mx, float my) {  // check if user clicked a button and return true/false 
        if (mx >= x-(stroke/300) && mx <= x+(stroke/300) && my <= y+(stroke/300) && my >= y-(stroke/300)) {
            return true;
        } else {
            return false;
        }
    }
};
struct Point {
    float x;
    float y;
    Color color;
    float stroke;

    Point() {
        x = 0.0f;
        y = 0.0f;
    }

    Point(float x, float y, Color color, float stroke) {
        this->x = x;
        this->y = y;
        this->color = color;
        this->stroke = stroke;
    }

    void draw() {
        glColor3f(color.r, color.g, color.b);
        glPointSize(stroke);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
};
struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    Color color;
    bool selected;
    bool pressed;
    bool button;
    

    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        selected = false;
        pressed = false;
        button = false;
    }

    Rectangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
        pressed = false;
        button = false;
    }

    Rectangle(float x, float y, float w, float h, Color color, bool button) {  // Rectangle shape
        this->x = x;  
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
        pressed = false;
        this->button = button;
    }

    void draw() { 
        if(button && pressed){
            color.colorSelect(Color(1.0f, 1.0f, 1.0f));
        }
        else if(button && !pressed){
            color.colorSelect(Color(0.8f, 0.8f, 0.8f));
        }

        glColor3f(color.r, color.g, color.b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        if (selected) {
            Rectangle outer(x, y, w, h, Color(1.0f, 1.0f, 1.0f));
            Rectangle inner(x + 0.02, y - 0.02, w - 0.04, h - 0.04, color);
            outer.draw();
            inner.draw();
        }
        
    }

    bool isClicked(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};
struct Square {   // Square shape
    float x;
    float y;
    float w;
    Color color;
    bool selected;
    
    Square() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
    }

    Square(float x, float y, float w, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->color = color;
        this->selected = false;
    }

    void draw() { 

        glColor3f(color.r, color.g, color.b);
        glBegin(GL_POLYGON);
            glVertex2f(x-(w/2), y+(w/2));
            glVertex2f(x-(w/2) + w, y+(w/2));
            glVertex2f(x-(w/2) + w, y+(w/2) - w);
            glVertex2f(x-(w/2), y+(w/2) - w);
        glEnd();

        if(selected){
            Square outer(x, y, w - 0.03, Color(1.0f, 1.0f, 1.0f));
            Square inner(x, y, w - 0.06, color);
            outer.draw();
            inner.draw();
        }
    }

    bool isClicked(float mx, float my) {
        if (mx >= x-(w/2) && mx <= x-(w/2) + w && my <= y+(w/2) && my >= y+(w/2) - w) {
            return true;
        } else {
            return false;
        }
    }
};
struct Texture {
    std::string imagePath;
    float x;
    float y;
    float w;
    float h;
    bool selected;
    
    unsigned char* imageData;
    int imageWidth;
    int imageHeight;
    int bitDepth;
    GLuint texture;

    Texture() {
        //
    }

    Texture(std::string imagePath, float x, float y, float w, float h) {
        this->imagePath = imagePath;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        selected = false;
    }

    void loadTexture() {
        stbi_set_flip_vertically_on_load(true);
        imageData = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &bitDepth, STBI_rgb_alpha);
        if (imageData == NULL) {
            std::cerr << "Failed to load texture file" << std::endl;
        } else {
            std::cout << "Texture file loaded successfully" << std::endl;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }

    void draw() {
        if (selected) {
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.8f, 0.8f, 0.8f);
        }
        
        glBegin(GL_POLYGON);
            glVertex2f(x, y - h);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y - h);
            glVertex2f(x, y);

            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        // Display texture
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Map texture to polygon
        glBegin(GL_POLYGON);
            // bottom left corner
            glTexCoord2f(0.0f, 0.0f); 
            glVertex2f(x, y - h);

            // top left corner
            glTexCoord2f(0.0f, 1.0f); 
            glVertex2f(x, y);

            // top right corner
            glTexCoord2f(1.0f, 1.0f); 
            glVertex2f(x + w, y);

            // bottom right corner
            glTexCoord2f(1.0f, 0.0f); 
            glVertex2f(x + w, y - h);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    bool isClicked(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};
struct Triangle {
    float x;
    float y;
    float w;
    Color color;
    bool selected;

    Triangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        selected = false;
    }

    Triangle(float x, float y, float w, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->color = color;
        this->selected = false;
    }

    void draw() { 
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y+(w/2));
            glVertex2f(x-(w/2), y-(w/2));
            glVertex2f(x+(w/2), y-(w/2));
        glEnd();

        if(selected){
            Triangle outer(x,y,w-0.02,Color(1.0f,1.0f, 1.0f));
            Triangle inner(x,y,w-0.05,color);
            outer.draw();
            inner.draw();
        }
        
    }

    bool isClicked(float mx, float my) {
        if (mx >= x-(w/2) && mx <= x+(w/2) && my <= y+(w/2) && my >= y-(w/2)) {
            return true;
        } else {
            return false;
        }
    }
};

enum TOOL {PENCIL, ERASER, SELECTOR, SQUARE, CIRCLE, TRIANGLE};
enum COLOR {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, BLACK, NONE};
enum STROKE {ONE, TWO, THREE};

struct PaintApp {
    Rectangle verticalToolbar;
    Rectangle horizontalToolbar;
    Rectangle canvas;

    Rectangle Colors[7];
    Rectangle redButton;
    Rectangle greenButton;
    Rectangle blueButton;
    Rectangle yellowButton;
    Rectangle magentaButton;
    Rectangle cyanButton;
    Rectangle blackButton;

    Color brushColor;
    float stroke = 10.0;

    Texture pencilButton;
    Texture eraserButton;
    Texture selectorButton;
    Rectangle squareButton;
    Rectangle circleButton;
    Rectangle triangleButton;

    Square square;
    Circle circle;
    Triangle triangle;

    Button clearButton;
    Rectangle stroke1;
    Rectangle stroke2;
    Rectangle stroke3;
    Rectangle one;
    Rectangle two;
    Rectangle three;


    TOOL selectedTool;
    COLOR selectedColor;
    STROKE selectedStroke;

    Point points[10000];
    int pCounter = 0;

    Square squares[1000];
    int sCounter = 0;

    Circle circles[1000];
    int cCounter = 0;

    Triangle triangles[1000];
    int tCounter = 0;

    int selectedSquare = -1;
    int selectedCircle = -1;
    int selectedTriangle = -1;

    // MAIN PAINT APP CODE //
    PaintApp() {
        verticalToolbar = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, Color(0.7f, 0.7f, 0.7f));
        horizontalToolbar = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.7f, 0.7f, 0.7f));
        canvas = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, Color(0.9f, 0.9f, 0.9f));

        // Red rectangle 
        Colors[0] = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f)); 
        // Blue rectangle
        Colors[1] = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 0.0f));
        // Green rectangle
        Colors[2] = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 1.0f));
        // Yellow rectangle
        Colors[3] = Rectangle(-0.2f, -0.8f, 0.2f, 0.2f, Color(1.0f, 1.0f, 0.0f));
        // Magenta rectangle
        Colors[4] = Rectangle(0.0f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 1.0f));
        // Cyan rectangle
        Colors[5] = Rectangle(0.2f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 1.0f));
        // Black rectangle
        Colors[6] = Rectangle(0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 0.0f));


        clearButton = Button("Clear", 0.7f, -0.8f);

        brushColor = Color(1.0f, 0.0f, 0.0f);

        pencilButton = Texture("assets/pencil.png", -1.0f, 1.0f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.8f, 0.2f, 0.2f);
        selectorButton = Texture("assets/mouse.png", -1.0f, 0.6f, 0.2f, 0.2f);

        squareButton = Rectangle(-1.0f, 0.4f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        circleButton = Rectangle(-1.0f, 0.2f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        triangleButton = Rectangle(-1.0f, 0.0f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        square = Square(-0.9f, 0.3f, 0.1f, Color(0.0f, 0.0f, 0.0f));
        circle = Circle(-0.9f, 0.1f,  20.0f, Color(0.0f, 0.0f, 0.0f));
        triangle = Triangle(-0.9f, -0.1, 0.1f, Color(0.0f, 0.0f, 0.0f));

        stroke1 = Rectangle(-1.0f, -0.2f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        stroke2 = Rectangle(-1.0f, -0.4f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        stroke3 = Rectangle(-1.0f, -0.6f, 0.2f, 0.2f, Color(0.8f, 0.8f, 0.8f), true);
        one = Rectangle(-1.0f, -0.285f, 0.2f, 0.03f, Color(0.0f, 0.0f, 0.0f));
        two = Rectangle(-1.0f, -0.47f, 0.2f, 0.06f, Color(0.0f, 0.0f, 0.0f));
        three = Rectangle(-1.0f, -0.6555f, 0.2f, 0.09f, Color(0.0f, 0.0f, 0.0f));

        selectedTool = PENCIL;
        selectedColor = RED;
    }

    void init() {
        pencilButton.loadTexture();
        eraserButton.loadTexture();
        selectorButton.loadTexture();
    }

    void exitEraserColor(){
        for(Rectangle selectedColor : Colors){
            if(selectedColor.selected == true){
                brushColor.colorSelect(selectedColor.color);
            }
        }
    }

    void unselectObjectsIndexes(){
        selectedSquare = -1;
        selectedCircle = -1;
        selectedTriangle = -1;
    }
    
    void unSelectSquares(){
        for (int i = 0; i < sCounter; i++){
            squares[i].selected = false;
        }
    }

    void deSelectCircles(){
        for (int i = 0; i < cCounter; i++){
            circles[i].selected = false;
        }
    }

    void deSelectTriangles(){
        for (int i = 0; i < tCounter; i++){
            triangles[i].selected = false;
        }
    }

    void leftMouseDown(float x, float y) {
        if (pencilButton.isClicked(x, y)) {
            selectedTool = PENCIL;
            exitEraserColor();
        } else if (eraserButton.isClicked(x, y)) {
            brushColor.colorSelect(canvas.color);
            selectedTool = ERASER;
            selectedColor = NONE;
        } else if (selectorButton.isClicked(x, y)){
            selectedTool = SELECTOR;
            selectedColor = NONE;
        } else if (squareButton.isClicked(x, y)){
            selectedTool = SQUARE;
            selectedColor = NONE;
            exitEraserColor();
        } else if (circleButton.isClicked(x, y)){
            selectedTool = CIRCLE;
            selectedColor = NONE;
            exitEraserColor();
        } else if (triangleButton.isClicked(x, y)){
            selectedTool = TRIANGLE;
            selectedColor = NONE;
            exitEraserColor();
        }

        if(stroke1.isClicked(x, y)){
            selectedStroke = ONE;
            stroke = 10.0f;
        } else if (stroke2.isClicked(x, y)){
            selectedStroke = TWO;
            stroke = 20.0f;
        } else if (stroke3.isClicked(x, y)){
            selectedStroke = THREE;
            stroke = 30.0f;
        }
        
        if (Colors[0].isClicked(x, y)) {
            selectedColor = RED;
            brushColor.colorSelect(Colors[0].color);
        } else if (Colors[1].isClicked(x, y)) {
            selectedColor = GREEN;
            brushColor.colorSelect(Colors[1].color);
        } else if (Colors[2].isClicked(x, y)) {
            selectedColor = BLUE;
            brushColor.colorSelect(Colors[2].color);
        } else if (Colors[3].isClicked(x, y)){
            selectedColor = YELLOW;
            brushColor.colorSelect(Colors[3].color);
        } else if (Colors[4].isClicked(x, y)){
            selectedColor = MAGENTA;
            brushColor.colorSelect(Colors[4].color);
        } else if (Colors[5].isClicked(x, y)){
            selectedColor = CYAN;
            brushColor.colorSelect(Colors[5].color);
        } else if (Colors[6].isClicked(x, y)){
            selectedColor = BLACK;
            brushColor.colorSelect(Colors[6].color);
        } else if (clearButton.isClicked(x, y)){
            pCounter = 0;
            sCounter = 0;
            cCounter = 0;
            tCounter = 0;
            clearButton.buttonPressed = true;
        }

        if (selectedTool == PENCIL || selectedTool == ERASER){
            unselectObjectsIndexes();
            unSelectSquares();
            deSelectCircles();
            deSelectTriangles();
            if(pCounter < 10000 && canvas.isClicked(x, y)){
                points[pCounter] = Point(x, y, brushColor, stroke);
                pCounter++;
            }
        } else if (selectedTool == SELECTOR){
            if(brushColor.r==0.9f && brushColor.g==0.9f && brushColor.b==0.9f ){
                exitEraserColor();
            }
            if(canvas.isClicked(x,y)){
                unselectObjectsIndexes();                
                unSelectSquares();
                deSelectCircles();
                deSelectTriangles(); 
            }
            //
            for(int i = sCounter-1; i >= 0; i--){
                if(squares[i].isClicked(x, y)){
                    selectedSquare = i;
                    squares[i].selected = true;
                }
            }
            for(int i = cCounter-1; i >= 0; i--){
                if(circles[i].isClicked(x, y)){
                    selectedCircle = i;
                    circles[i].selected = true;
                }
            }
            for(int i = tCounter-1; i >= 0; i--){
                if(triangles[i].isClicked(x, y)){
                    selectedTriangle = i;
                    triangles[i].selected = true;
                }
            }
            if(selectedSquare != -1 && !canvas.isClicked(x, y)){
                squares[selectedSquare].color = brushColor;
                squares[selectedSquare].w = stroke/100;
            }
            if(selectedCircle != -1 && !canvas.isClicked(x, y)){
                circles[selectedCircle].color =  brushColor;
                circles[selectedCircle].stroke = stroke*1.5;
            }
            if(selectedTriangle != -1 && !canvas.isClicked(x, y)){
                triangles[selectedTriangle].color =  brushColor;
                triangles[selectedTriangle].w = stroke/100;
            }

        } else if (selectedTool == SQUARE){
            unselectObjectsIndexes();
            for (int i = 0; i < sCounter; i++){
                    squares[i].selected = false;
            }
            if(sCounter < 1000 && canvas.isClicked(x, y)){
                squares[sCounter] = Square(x, y, stroke/100, brushColor);
                sCounter++;
            }
        } else if (selectedTool == CIRCLE){
            unselectObjectsIndexes();
            for (int i = 0; i < sCounter; i++){
                    squares[i].selected = false;
            }
            if(cCounter < 1000 && canvas.isClicked(x, y)){
                circles[cCounter] = Circle(x, y, stroke*1.5, brushColor);
                cCounter++;
            }
        } else if (selectedTool == TRIANGLE){
            unselectObjectsIndexes();
            for (int i = 0; i < sCounter; i++){
                    squares[i].selected = false;
            }
            if(tCounter < 1000 && canvas.isClicked(x, y)){
                triangles[tCounter] = Triangle(x, y, stroke/100, brushColor);
                tCounter++;
            }
        }

    }

    void leftMouseUp(float x, float y) {
        clearButton.buttonPressed = false; 
    }

    void rightMouseDown(float x, float y) {
        // 
    }

    void rightMouseUp(float x, float y) {
        // 
    }

    void mouseMotion(float x, float y) {
        if (selectedTool == PENCIL || selectedTool == ERASER){
            if(pCounter < 10000 && canvas.isClicked(x, y)){
                points[pCounter] = Point(x, y, brushColor, stroke);
                pCounter++;
            }
        } else if (selectedTool == SELECTOR){
            for(int i = 0; i < sCounter; i++){
                if(squares[i].isClicked(x,y)){
                    squares[i].x = x;
                    squares[i].y = y;
                }
            }
            for(int i = 0; i < cCounter; i++){
                if(circles[i].isClicked(x, y)){
                    circles[i].x = x;
                    circles[i].y = y;
                }
            }
            for(int i = 0; i < tCounter; i++){
                if(triangles[i].isClicked(x, y)){
                    triangles[i].x = x;
                    triangles[i].y = y;
                }
            }
        }
    }

    void keyboardDown(unsigned char key, float x, float y) {

    }



// Render objects 



    void render() {
        if (selectedTool == PENCIL) {
            pencilButton.selected = true;
            eraserButton.selected = false;
            selectorButton.selected = false;
            squareButton.pressed = false;
            circleButton.pressed = false;
            triangleButton.pressed = false;
        } else if (selectedTool == ERASER) {
            pencilButton.selected = false;
            eraserButton.selected = true;
            selectorButton.selected = false;
            squareButton.pressed = false;
            circleButton.pressed = false;
            triangleButton.pressed = false;
        } else if (selectedTool == SELECTOR) {
            pencilButton.selected = false;
            eraserButton.selected = false;
            selectorButton.selected = true;
            squareButton.pressed = false;
            circleButton.pressed = false;
            triangleButton.pressed = false;
        } else if (selectedTool == SQUARE) {
            pencilButton.selected = false;
            eraserButton.selected = false;
            selectorButton.selected = false;
            squareButton.pressed = true;
            circleButton.pressed = false;
            triangleButton.pressed = false;
        } else if (selectedTool == CIRCLE) {
            pencilButton.selected = false;
            eraserButton.selected = false;
            selectorButton.selected = false;
            squareButton.pressed = false;
            circleButton.pressed = true;
            triangleButton.pressed = false;
        } else if (selectedTool == TRIANGLE) {
            pencilButton.selected = false;
            eraserButton.selected = false;
            selectorButton.selected = false;
            squareButton.pressed = false;
            circleButton.pressed = false;
            triangleButton.pressed = true;
        }

        if (selectedColor == RED) {
            Colors[0].selected = true;
            Colors[1].selected = false;
            Colors[2].selected = false;
            Colors[3].selected = false;
            Colors[4].selected = false;
            Colors[5].selected = false;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        } else if (selectedColor == GREEN) {
            Colors[0].selected = false;
            Colors[1].selected = true;
            Colors[2].selected = false;
            Colors[3].selected = false;
            Colors[4].selected = false;
            Colors[5].selected = false;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        } else if (selectedColor == BLUE) {
            Colors[0].selected = false;
            Colors[1].selected = false;
            Colors[2].selected = true;
            Colors[3].selected = false;
            Colors[4].selected = false;
            Colors[5].selected = false;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        }
        else if (selectedColor == YELLOW){
            Colors[0].selected = false;
            Colors[1].selected = false;
            Colors[2].selected = false;
            Colors[3].selected = true;
            Colors[4].selected = false;
            Colors[5].selected = false;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        }
        else if (selectedColor == MAGENTA){
            Colors[0].selected = false;
            Colors[1].selected = false;
            Colors[2].selected = false;
            Colors[3].selected = false;
            Colors[4].selected = true;
            Colors[5].selected = false;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        }
        else if  (selectedColor == CYAN){
            Colors[0].selected = false;
            Colors[1].selected = false;
            Colors[2].selected = false;
            Colors[3].selected = false;
            Colors[4].selected = false;
            Colors[5].selected = true;
            Colors[6].selected = false;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        }
        else if (selectedColor == BLACK){
            Colors[0].selected = false;
            Colors[1].selected = false;
            Colors[2].selected = false;
            Colors[3].selected = false;
            Colors[4].selected = false;
            Colors[5].selected = false;
            Colors[6].selected = true;
            if(selectedTool == ERASER){
                selectedTool = PENCIL;
            }
        }

        if (selectedStroke == ONE){
            stroke1.pressed = true;
            stroke2.pressed = false;
            stroke3.pressed = false;
        }
        else if (selectedStroke == TWO){
            stroke1.pressed = false;
            stroke2.pressed = true;
            stroke3.pressed = false;
        }
        else if (selectedStroke == THREE){
            stroke1.pressed = false;
            stroke2.pressed = false;
            stroke3.pressed = true;
        }

        canvas.draw();
        for (int i = 0; i < sCounter; i++){
            squares[i].draw();
        }
        for (int i = 0; i < cCounter; i++){
            circles[i].draw();
        }
        for (int i = 0; i < tCounter; i++){
            triangles[i].draw();
        }
        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }
        verticalToolbar.draw();
        horizontalToolbar.draw();

        Colors[0].draw();
        Colors[1].draw();
        Colors[2].draw();
        Colors[3].draw();
        Colors[4].draw();
        Colors[5].draw();
        Colors[6].draw();

        clearButton.draw();

        pencilButton.draw();
        eraserButton.draw();
        selectorButton.draw();
        squareButton.draw();
        circleButton.draw();
        triangleButton.draw();
        square.draw();
        circle.draw();
        triangle.draw();
        stroke1.draw();
        stroke2.draw();
        stroke3.draw();
        one.draw();
        two.draw();
        three.draw();

        
    }
};

#endif
