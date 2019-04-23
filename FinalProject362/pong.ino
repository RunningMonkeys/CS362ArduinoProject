// -*- c++ -*-

/*
  A simple Pong game
  source : https://create.arduino.cc/projecthub/nickthegreek82/arduino-pong-game-oled-display-b768ad
 modified to work with a HVGA 480x320 arduino mega shield
 and take input over serial instead of directly
 */




void pong() {
  
    //bool update = false;
    unsigned long time = millis();
    drawCourt();
    static bool up_state = false;
    static bool down_state = false;
    if(Serial.available())
    {
      serialInput();
        if(ypos<400)
        {
             up_state = true;
         }
       if(ypos>600)
      {
         down_state = true;
       }
        
      }

    
    
    
    //up_state |= (digitalRead(UP_BUTTON) == LOW);
    //down_state |= (digitalRead(DOWN_BUTTON) == LOW);

    if(time > ball_update) {
        int new_x = ball_x + ball_dir_x;
        int new_y = ball_y + ball_dir_y;

        // Check if we hit the vertical walls
        if(new_x == 0 || new_x == VERT_WALL) {
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        // Check if we hit the horizontal walls.
        if(new_y == 0 || new_y == HORIZ_WALL) {
            ball_dir_y = -ball_dir_y;
            new_y += ball_dir_y + ball_dir_y;
        }

        // Check if we hit the CPU paddle
        if(new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) {
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        // Check if we hit the player paddle
        if(new_x == PLAYER_X
           && new_y >= player_y
           && new_y <= player_y + PADDLE_HEIGHT)
        {
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }
        myGLCD.setColor(0,0,0); //color black
        myGLCD.drawPixel(ball_x, ball_y);
        myGLCD.drawRect(ball_x - 1, ball_y - 1, ball_x +1, ball_y + 1);
        myGLCD.setColor(255,255,255); //color white
        myGLCD.drawRect(new_x - 1, new_y - 1, new_x +1, new_y + 1);
        myGLCD.drawPixel(new_x, new_y);
        
        ball_x = new_x;
        ball_y = new_y;

        ball_update += BALL_RATE;
    }

    if(time > paddle_update) {
        paddle_update += PADDLE_RATE;

        // CPU paddle
        myGLCD.setColor(0,0,0); // color black
        myGLCD.drawLine(CPU_X, cpu_y, CPU_X, cpu_y + PADDLE_HEIGHT);
        const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
        if(cpu_y + half_paddle > ball_y) {
            cpu_y -= 1;
        }
        if(cpu_y + half_paddle < ball_y) {
            cpu_y += 1;
        }
        if(cpu_y < 1) cpu_y = 1;
        if(cpu_y + PADDLE_HEIGHT > HORIZ_WALL) cpu_y = HORIZ_WALL - PADDLE_HEIGHT;
        myGLCD.setColor(255,255,255); //color black
        myGLCD.drawLine(CPU_X, cpu_y, CPU_X, cpu_y + PADDLE_HEIGHT);

        // Player paddle
        myGLCD.setColor(0,0,0); //color white
        myGLCD.drawLine(PLAYER_X, player_y, PLAYER_X, player_y + PADDLE_HEIGHT);
        if(up_state) {
            player_y -= 1;
        }
        if(down_state) {
            player_y += 1;
        }
        up_state = down_state = false;
        if(player_y < 1) player_y = 1;
        if(player_y + PADDLE_HEIGHT > HORIZ_WALL) player_y = HORIZ_WALL - PADDLE_HEIGHT;
        myGLCD.setColor(255,255,255);
        myGLCD.drawLine(PLAYER_X, player_y, PLAYER_X, player_y + PADDLE_HEIGHT);

    }

}
