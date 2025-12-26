# Martial-Arts-Studio-Management-System

Project Overview
This project is a dynamic management system designed to handle the daily operations of a martial arts studio. It provides a centralized platform for organizing training sessions, managing member information, and tracking studio resources efficiently.

Main Capabilities

Member Management: The system tracks detailed information for both trainers and trainees, including personal data, seniority levels, and subscription details.
Training Coordination: Users can schedule and manage training sessions, linking specific trainers to designated rooms at set dates and times.
Resource Tracking: Includes a room management module to oversee studio spaces and a tracking system for trainers' personal equipment.
Data Flexibility: Supports saving and loading studio data through both text and binary files, allowing for easy data persistence.
Search & Organization: Provides tools to sort trainees by various criteria (such as ID, age, or subscription price) and search for specific members within the database.

Key Technical Features

Object Modeling: The system is built using a modular structure with custom structs to represent entities like Person, Trainer, Room, and Equipment.
Efficient Data Structures: Uses a combination of dynamic arrays and linked lists (specifically for room management) to handle data growth smoothly.

Smart Compression: To save storage space, the system implements bit-manipulation techniques to compress equipment data in binary files, reducing the size of certain structures from 12 bytes to just 2 bytes.

Validation Logic: Includes a specialized algorithm to verify the integrity of ID numbers, ensuring data accuracy during member registration.
