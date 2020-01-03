#ifndef NOTIFICATIONTYPE_H
#define NOTIFICATIONTYPE_H

// Notifications are only sent to objects that are registered
// for that notification class
enum class NotificationType
{
    Collision, // Sent when an object is in collision with another object
    Input,     // Sent when a specific input is received
    Frame      // Sent on each frame render
};

#endif