#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>

#include "exportdata.h"

namespace vnotex
{
    class Exporter : public QObject
    {
        Q_OBJECT
    public:
        // We need the QWidget as parent.
        explicit Exporter(QWidget *p_parent);
    };
}

#endif // EXPORTER_H
