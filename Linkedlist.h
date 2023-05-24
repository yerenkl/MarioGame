#pragma once
#include "Common.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class LinkedList
{
    RenderWindow* window;
public:
    Object* head;
    LinkedList(RenderWindow* window)
    {
        this->window = window;
        head = nullptr;
    }

    void insertTurtle(int heading, float t_v)
    {
       
        Object* newTurtle = new Turtle(window, heading, t_v);
        
        if (head == nullptr)
        {
            
            head = newTurtle;
        }
        else
        {
            Object* temp = head;
            while (temp->next != nullptr)
            {
                
                temp = temp->next;
            }
            temp->next = newTurtle;
        }
        
    }

    void drawAll()
    {
        Object* temp = head;
        
        while (temp != nullptr)
        {
            temp->update();
            temp = temp->next;
        }
    }

    int elementNumber()
    {
        int n=0;
        Object* temp = head;

        while (temp != nullptr)
        {
            n++;
            temp = temp->next;
        }
        return n;
    }

    void velocitySet(float k)
    {
        Object* temp = head;

        while (temp != nullptr)
        {
            temp->setVelocityX(k);
            temp = temp->next;
        }
    }

    void destroyAll()
    {
        Object* temp = head;
        while (temp != nullptr)
        {
            Object* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }
};