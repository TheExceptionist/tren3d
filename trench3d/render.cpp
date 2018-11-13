#include "render.h"

Render::Render(Display& display)
    : m_display(display)
{
    /*#ifdef DEBUG
       // fillMap();
    #endif*/
}

Render::~Render()
{

}

e_std::e_bool Render::init()
{
    e_std::e_bool success = TRUE;

    return success;
}

void Render::setPlayer(Entity* player)
{
    m_player = player;
}

void Render::update()
{
    drawCeil(DARK_BLUE);
    drawFloor(GRAY);
    drawWalls();
}

void Render::drawCeil(const e_std::color_t& color)
{
    m_display.fillRect(0, 0, m_display.getWidth(), m_display.getHeight()/2, &color);
}

void Render::drawFloor(const e_std::color_t& color)
{
    m_display.fillRect(0, m_display.getHeight()/2, m_display.getWidth(), m_display.getHeight()/2, &color);
}

void Render::drawWalls()
{
    using namespace e_math;
    //Get the plane perp to the direction the player is facing
    vec3f plane = m_player->getDir()->rotate2D(90);
    vec3f* pos = m_player->getPos();
	e_std::e_word width = m_display.getWidth();
    //printf("Check 1\n");

    for(int col = 0; col < width; col++)
    {
        //printf("Check 2\n");
        double plane_scalar = ((double)(2 * col) / (double)width) - 1;
        vec3f plane_pos = (plane * plane_scalar);
        vec3f ray = *m_player->getDir() + plane_pos; 

        vec3i map_pos(0, 0, 0);
        map_pos[X_POS] = (int)(*pos)[X_POS];
        map_pos[Y_POS] = (int)(*pos)[Y_POS];

        double delta_ray_x = sqrt((1 + (ray[Y_POS]*ray[Y_POS]) / (ray[X_POS]*ray[X_POS])));
        double delta_ray_y = sqrt((1 + (ray[X_POS]*ray[X_POS]) / (ray[Y_POS]*ray[Y_POS])));

        vec3d delta_ray(delta_ray_x , delta_ray_y, 0);
        vec3d ray_dist(0, 0, 0);
        double wallDist;

        vec3i step(0, 0, 0);

        e_std::e_bool hit = FALSE;
        int side;
        //printf("Check 3\n");
        if(delta_ray[X_POS] > 0)
        {
            step[X_POS] = 1;
            ray_dist[X_POS] = delta_ray[X_POS] * ((map_pos[X_POS] + 1) - (*pos)[X_POS]); 
        }
        else
        {
            step[X_POS] = -1;
            ray_dist[X_POS] = delta_ray[X_POS] * (map_pos[X_POS] - (*pos)[X_POS]); 
        }

        if(delta_ray[Y_POS] > 0)
        {
            step[Y_POS] = 1;
            ray_dist[Y_POS] = delta_ray[Y_POS] * ((map_pos[Y_POS] + 1) - (*pos)[Y_POS]); 
        }
        else
        {
            step[Y_POS] = -1;
            ray_dist[Y_POS] = delta_ray[Y_POS] * (map_pos[Y_POS] - (*pos)[Y_POS]); 
        }

        //printf("Check 4\n");
        while(!hit)
        {
            //printf("Check 4.1 (%d, %d)\n", map_pos[X_POS], map_pos[Y_POS]);

            if(ray_dist[X_POS] < ray_dist[Y_POS])
            {
                ray_dist[X_POS] += delta_ray[X_POS];
                map_pos[X_POS] += step[X_POS];
                side = NS;
            }
            else
            {
                ray_dist[Y_POS] += delta_ray[Y_POS];
                map_pos[Y_POS] += step[Y_POS];
                side = EW;
            }

            if(m_map[map_pos[X_POS]][map_pos[X_POS]] > 0) hit = TRUE;
        }

        //printf("Check 5\n");
        if (!side) wallDist = (map_pos[X_POS] - (*pos)[X_POS] + (1 - step[X_POS]) / 2) / ray[X_POS];
        else wallDist = (map_pos[Y_POS] - (*pos)[Y_POS] + (1 - step[Y_POS]) / 2) / ray[Y_POS];

        int col_height, window_height = m_display.getHeight();

        //printf("wallDist: %f\n", wallDist);
        if(wallDist > 0.01) 
        {
            col_height = abs((int)(window_height / wallDist));
            //printf("wallDist > 0\n");
        }
		else 
        {
            //printf("wallDist <= 0, Height %d\n", window_height);
            col_height = window_height;
        }

        int draw_start = -col_height / 2  + window_height/2;
        //printf("Draw Start: %d Window Height: %d Height: %d Result: %d\n", draw_start, -1*window_height/2, col_height, -1*m_display.getHeight()/2 + col_height/2);
        if(draw_start < 0) draw_start = 0;
        //printf("Draw Start: %d\n", draw_start);
        int draw_end = col_height / 2 + window_height / 2;
        if(draw_end > window_height) draw_end = window_height - 1;

        e_std::color_t wall_color;

        switch(m_map[map_pos[X_POS]][map_pos[X_POS]])
        {
            case 1:
            {
                wall_color = RED;
            } break;
            default:
                wall_color = GREEN;
        }

        //printf("Col: %d Start: %d End: %d Col Height: %d Display Height: %u\n", col, draw_start, draw_end, col_height,window_height);

        if(side == EW) wall_color /= 2;
	
        m_display.fillRect(col, draw_start, 1, draw_end, &wall_color);
        //m_display.fillRect(0, draw_start, 1, draw_end, &wall_color);
        //m_display.fillRect(1, draw_start, 1, draw_end, &wall_color);
    }
}

#ifdef DEBUG
/*void Render::fillMap()
{
    for(int y = 0; y < MAX_MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAX_MAP_WIDTH; x++)
        {
            if(x == 0) m_map[y][x] = 1; 
            if(y == 0) m_map[y][x] = 1; 
            if(x == MAX_MAP_WIDTH - 1) m_map[y][x] = 1; 
            if(y == MAX_MAP_HEIGHT - 1) m_map[y][x] = 1; 
        }
    }
}*/
#endif

