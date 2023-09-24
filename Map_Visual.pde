import processing.serial.*;

Serial arduinoPort;
int[] distances = new int[3];
int radarDistance;
int radarAngle;
int radarDirection = 1;
boolean radarComplete = false;

void setup() {
  size(800, 600);
  smooth();
  
  // Adjust the port name and baud rate according to your setup
  arduinoPort = new Serial(this, "COM8", 9600);
}

void draw() {
  background(255);
  
  if (arduinoPort.available() > 0) {
    String data = arduinoPort.readStringUntil('\n');
    
    if (data != null && !data.isEmpty()) {
      data = data.trim();
      String[] values = data.split(",");
      
      if (values.length == 5) {
        for (int i = 0; i < 3; i++) {
          if (!values[i].isEmpty()) {
            distances[i] = Integer.parseInt(values[i]);
          }
        }
        
        if (!values[3].isEmpty()) {
          radarDistance = Integer.parseInt(values[3]);
        }
        
        if (!values[4].isEmpty()) {
          radarAngle = Integer.parseInt(values[4]);
        }
        
        radarComplete = true;
      }
    }
  }
  
  drawMap();
  
  if (radarComplete) {
    drawRadar();
  }
}

void drawMap() {
  float mapX = width / 2;
  float mapY = height / 2;
  float mapWidth = 400;  // Width of the map (in pixels)
  float mapHeight = 400; // Height of the map (in pixels)
  
  // Draw the walls
  stroke(0);
  fill(150);
  rectMode(CENTER);
  rect(mapX, mapY, mapWidth, mapHeight);

  // Draw the walls lines
  float wallX = mapX - mapWidth / 2;
  float wallY = mapY - mapHeight / 2;

  strokeWeight(2);
  stroke(0);
  line(wallX, mapY, wallX + mapWidth, mapY); // Horizontal line at y-axis (0 and 180 degrees)
  line(mapX, wallY, mapX, wallY + mapHeight); // Vertical line at x-axis (90 degrees)

  // Draw the objects detected by the sensors
  for (int i = 0; i < 3; i++) {
    float angle = radians(i * 90);
    float x = mapX + cos(angle) * distances[i] * mapWidth / 400;
    float y = mapY + sin(angle) * distances[i] * mapHeight / 400;

    noFill();
    stroke(255, 0, 0);

    if (i == 0) {
      line(x, wallY, x, wallY + mapHeight); // Vertical line for Sensor 1
    } else if (i == 1) {
      line(wallX, y, wallX + mapWidth, y); // Horizontal line for Sensor 2
    } else if (i == 2) {
      line(x, wallY, x, wallY + mapHeight); // Vertical line for Sensor 3
    }
  }
}

void drawRadar() {
  float radarX = width / 2;
  float radarY = height / 2;
  float radius = min(width, height) * 0.4; // Radius of the radar circle
  float angleStep = radians(5); // Step size for the radar angle

  // Draw radar circle
  stroke(0);
  noFill();
  ellipse(radarX, radarY, radius * 2, radius * 2);

  // Draw radar lines
  for (float angle = 0; angle < TWO_PI; angle += angleStep) {
    float startX = radarX + cos(angle) * radius;
    float startY = radarY + sin(angle) * radius;
    float endX = radarX + cos(angle) * radius * 1.2;
    float endY = radarY + sin(angle) * radius * 1.2;
    stroke(0);
    line(startX, startY, endX, endY);
  }

  // Draw radar sweep line
  float sweepStartX = radarX + cos(radians(radarAngle)) * radius;
  float sweepStartY = radarY + sin(radians(radarAngle)) * radius;
  float sweepEndX = radarX + cos(radians(radarAngle)) * radius * 1.2;
  float sweepEndY = radarY + sin(radians(radarAngle)) * radius * 1.2;
  stroke(255, 0, 0);
  line(sweepStartX, sweepStartY, sweepEndX, sweepEndY);

  // Draw radar obstacle line
  if (radarDistance > 0) {
    float obstacleX = radarX + cos(radians(radarAngle)) * radarDistance * radius / 400;
    float obstacleY = radarY + sin(radians(radarAngle)) * radarDistance * radius / 400;
    stroke(0, 255, 0);
    line(radarX, radarY, obstacleX, obstacleY);
  }
}
