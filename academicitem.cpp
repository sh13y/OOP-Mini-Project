#include "academicitem.h"
#include <QDateTime>

// Constructor implementation
AcademicItem::AcademicItem(Type type, const QString &title, const QString &description,
                          const QDateTime &dateTime, int durationMinutes)
    // Initialize all member variables using initialization list
    : m_type(type)
    , m_title(title)
    , m_description(description)
    , m_dateTime(dateTime)
    , m_durationMinutes(durationMinutes)
{
    // No additional initialization needed
}

// Check if a deadline is approaching (within 24 hours)
bool AcademicItem::isDeadlineApproaching() const
{
    // Only check deadlines, not lectures
    if (m_type != Deadline)
        return false;

    // Get current time for comparison
    QDateTime now = QDateTime::currentDateTime();
    
    // Calculate how many hours until the deadline
    int hoursUntilDeadline = now.secsTo(m_dateTime) / 3600;
    
    // Return true if deadline is:
    // - Less than or equal to 24 hours away
    // - Not already passed (>= 0 hours)
    return hoursUntilDeadline <= 24 && hoursUntilDeadline >= 0;
} 