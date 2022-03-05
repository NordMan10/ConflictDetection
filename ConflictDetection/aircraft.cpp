#include "aircraft.h"

Aircraft::Aircraft(std::string id, AircraftPath path, IAircraftObserver* observer, std::string entryMoment,
                   int aircraftListIndex, int timerTickValue) :
    m_Path(path),
    m_ActivePathStartPoint(path.getPath()[0]),
    m_ActivePathEndPoint(path.getPath()[1])
{
    m_Id = id;
    m_EntryMoment = entryMoment;
    m_TimerTickValue = timerTickValue;
    m_Image = QPixmap(":/resources/img/aircraft2.png");
    m_DataCardRect = QRectF(5, -20, 36, 12);

    m_AircraftObservers.push_back(observer);
    m_AircraftListIndex = aircraftListIndex;

    m_X = m_Path.getPath()[0].x();
    m_Y = m_Path.getPath()[0].y();
    m_Z = m_Path.getPath()[0].z();

    m_X_inMeters = m_Path.getPath()[0].x_inMeters();
    m_Y_inMeters = m_Path.getPath()[0].y_inMeters();
    m_Z_inMeters = m_Path.getPath()[0].z_inMeters();

    calculateHorAngle();
    calculateShifts(timerTickValue);

    initGraphicsItems();
}

void Aircraft::initGraphicsItems() {
    create_ISZ_Rectangle();
    create_IPSZ_Rectangle();

    //m_IPSZ_Rectangle = QRect((-1) * ISZ_Width, ((-1) * IPSZ_Length) + (ISZ_Length), ISZ_Width * 2, IPSZ_Length);
}

const QString& Aircraft::getTextForDataCard() {
    m_TextForDataCard = QString::fromStdString("  " + m_Id) + QString("\n") +
                        QString::fromStdString("  " + m_EntryMoment) + QString("\n") +
                        QString("  x: " + QString::number(std::round(m_X_inMeters)) + "; " +
                                "  y: " + QString::number(std::round(m_Y_inMeters)) + "; " +
                                "  z: " + QString::number(std::round(m_Z_inMeters)) + "; " + QString("\n") +
                        QString("  Скорость: ") + QString::number(m_Velocity) + " м/с");

    return m_TextForDataCard;
}

const QRectF& Aircraft::getDataCardRect() {
    return m_DataCardRect;
}

std::string Aircraft::getId() const {
    return m_Id;
}

QPixmap& Aircraft::getImage() {
    return m_Image;
}

double Aircraft::x() const {
    return m_X;
}

double Aircraft::y() const {
    return m_Y;
}

double Aircraft::z() const {
    return m_Z;
}

int Aircraft::x_inMeters() const {
    return m_X_inMeters;
}

int Aircraft::y_inMeters() const {
    return m_Y_inMeters;
}

int Aircraft::z_inMeters() const {
    return m_Z_inMeters;
}

AircraftPath& Aircraft::getPath() {
    return m_Path;
}

int Aircraft::getDangerRadius() const {
    return m_DangerRadius;
}

int Aircraft::getImageWidth() const {
    return m_ImageWidth;
}

int Aircraft::getImageHeight() const {
    return m_ImageHeight;
}

int Aircraft::getISZ_Width() const {
    return m_ISZ_Width;
}

int Aircraft::getISZ_Length() const {
    return m_ISZ_Length;
}

int Aircraft::get_IPSZ_Length() const {
    return m_Velocity * m_PredictingInterval;
}

double Aircraft::getVelocityX() const {
    return m_VelocityX;
}

double Aircraft::getVelocityY() const {
    return m_VelocityY;
}

double Aircraft::getVelocityZ() const {
    return m_VelocityZ;
}

QPolygon& Aircraft::get_ISZ_Rectangle() {
    return m_ISZ_Rectangle;
}

//QRect& Aircraft::get_IPSZ_Rectangle() {
//    return m_IPSZ_Rectangle;
//}

QPolygon& Aircraft::get_IPSZ_Rectangle() {
    return m_IPSZ_Rectangle;
}

QPolygon& Aircraft::getShifted_IPSZ_Rectangle() {
    for (int i = 0; i < m_IPSZ_Rectangle.count(); i++) {
        auto point = m_IPSZ_Rectangle.point(i);
        m_Shifted_IPSZ_Rectangle.setPoint(i, point.x() + m_X, point.y() + m_Y);
    }
    return m_Shifted_IPSZ_Rectangle;
}

double Aircraft::getHorizontalAngle() const {
    return m_AngleHor;
}

void Aircraft::calculateHorAngle() {
    double dx = (-1) * (m_ActivePathStartPoint.x_inMeters() - m_ActivePathEndPoint.x_inMeters());
    double dy = m_ActivePathStartPoint.y_inMeters() - m_ActivePathEndPoint.y_inMeters();

    m_AngleHor = std::atan2(dy, dx) * 180 / PI;
}

void Aircraft::calculateShifts(int timerTickValue) {
    double angleHor = getHorizontalAngle();

    m_VelocityX = (m_Velocity * std::cos(angleHor * PI / 180));
    m_VelocityY = (-1) * (m_Velocity * std::sin(angleHor * PI / 180));
    //m_VelocityZ = (m_Velocity * std::sin(angleV * PI / 180)) / (double)(1000 / timerTickValue);

    double velocityXForShift = m_VelocityX / (double)(1000 / timerTickValue);
    double velocityYForShift = m_VelocityY / (double)(1000 / timerTickValue);

    m_XShift_inMeters = velocityXForShift;
    m_YShift_inMeters = velocityYForShift;

    m_XShift = velocityXForShift / Convert::s_MetersInPixel;
    m_YShift = velocityYForShift / Convert::s_MetersInPixel;
}

void Aircraft::updateData(int timerTickValue) {
    m_X += m_XShift;
    m_Y += m_YShift;

    m_X_inMeters += m_XShift_inMeters;
    m_Y_inMeters += m_YShift_inMeters;

    handleArrivalToMiddlePoint();
    handleArrivalToEndPoint();

    conflictDetection();
}

void Aircraft::handleArrivalToMiddlePoint() {
    if (isAircraftAtPoint(m_ActivePathEndPoint)) {
        if (m_ActivePathEndPoint != m_Path.getPath().back()) {
            m_ActivePathStartPoint = m_ActivePathEndPoint;
            m_ActivePathEndPoint = getNextPathPoint(m_ActivePathStartPoint);

            calculateHorAngle();
            calculateShifts(m_TimerTickValue);

            create_ISZ_Rectangle();
            create_IPSZ_Rectangle();
        }
    }
}

void Aircraft::handleArrivalToEndPoint() {
    CDPoint endPoint = m_Path.getPath()[m_Path.getPath().size() - 1];
    if (isAircraftAtPoint(endPoint)) {
        for (int i = 0; i < m_AircraftObservers.size(); i++) {
            m_AircraftObservers[i]->updateAircraftData(getId());
        }
        m_AircraftObservers.clear();
        m_XShift = m_YShift = m_XShift_inMeters = m_YShift_inMeters = 0;
    }
}

void Aircraft::create_ISZ_Rectangle() {
    double angleHor = (-1) * getHorizontalAngle() * PI / 180;

    QPoint p1(std::round(Convert::ConvertMetersToPixelsKeepSign((get_IPSZ_Length() - m_ISZ_Length) * std::cos(angleHor) - ((-1) * m_ISZ_Width * std::sin(angleHor)))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((get_IPSZ_Length() - m_ISZ_Length) * std::sin(angleHor) + ((-1) * m_ISZ_Width * std::cos(angleHor)))));
    QPoint p2(std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::cos(angleHor) - ((-1) * m_ISZ_Width * std::sin(angleHor)))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::sin(angleHor) + ((-1) * m_ISZ_Width * std::cos(angleHor)))));
    QPoint p3(std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::cos(angleHor) - m_ISZ_Width * std::sin(angleHor))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::sin(angleHor) + m_ISZ_Width * std::cos(angleHor))));
    QPoint p4(std::round(Convert::ConvertMetersToPixelsKeepSign((get_IPSZ_Length() - m_ISZ_Length) * std::cos(angleHor) - m_ISZ_Width * std::sin(angleHor))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((get_IPSZ_Length() - m_ISZ_Length) * std::sin(angleHor) + m_ISZ_Width * std::cos(angleHor))));

    m_IPSZ_Rectangle = QPolygon(QVector<QPoint>{p1, p2, p3, p4});
    m_Shifted_IPSZ_Rectangle = QPolygon(QVector<QPoint>{p1, p2, p3, p4});
}

void Aircraft::create_IPSZ_Rectangle() {
    double angleHor = (-1) * getHorizontalAngle() * PI / 180;

    QPoint p11(std::round(Convert::ConvertMetersToPixelsKeepSign(m_ISZ_Length * std::cos(angleHor) - ((-1) * m_ISZ_Width * std::sin(angleHor)))),
              std::round(Convert::ConvertMetersToPixelsKeepSign(m_ISZ_Length * std::sin(angleHor) + ((-1) * m_ISZ_Width * std::cos(angleHor)))));
    QPoint p12(std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::cos(angleHor) - ((-1) * m_ISZ_Width * std::sin(angleHor)))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::sin(angleHor) + ((-1) * m_ISZ_Width * std::cos(angleHor)))));
    QPoint p13(std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::cos(angleHor) - m_ISZ_Width * std::sin(angleHor))),
              std::round(Convert::ConvertMetersToPixelsKeepSign((-1) * m_ISZ_Length * std::sin(angleHor) + m_ISZ_Width * std::cos(angleHor))));
    QPoint p14(std::round(Convert::ConvertMetersToPixelsKeepSign(m_ISZ_Length * std::cos(angleHor) - m_ISZ_Width * std::sin(angleHor))),
              std::round(Convert::ConvertMetersToPixelsKeepSign(m_ISZ_Length * std::sin(angleHor) + m_ISZ_Width * std::cos(angleHor))));

    m_ISZ_Rectangle = QPolygon(QVector<QPoint>{p11, p12, p13, p14});
}

// Значение погрешностей нужно вынести!
bool Aircraft::isAircraftAtPoint(CDPoint point) {
    return (std::abs(x_inMeters() - point.x_inMeters()) < std::abs(m_XShift_inMeters / 1.5) &&
            std::abs(y_inMeters() - point.y_inMeters()) < std::abs(m_YShift_inMeters / 1.5));
}

CDPoint Aircraft::getNextPathPoint(CDPoint point) {
    for (int i = 0; i < m_Path.getPath().size(); i++) {
        if (m_Path.getPath()[i] == point)
            return m_Path.getPath()[i + 1];
    }

    throw std::invalid_argument("The argument point is not contained in the aircraft's path");
}

// Попробуй поменять на метры (расчет в пикселях может давать сильные неточности)
bool Aircraft::isAircraftPotentiallyDangerous(const Aircraft& aircraft) {
    return std::pow(aircraft.x_inMeters() - x_inMeters(), 2) +
            std::pow(aircraft.y_inMeters() - y_inMeters(), 2) <= std::pow(m_DangerRadius, 2);
}

std::vector<std::reference_wrapper<Aircraft>>& Aircraft::getPotentiallyDangerousAircrafts() {
    return m_PotentiallyDangerousAircrafts;
}

void Aircraft::addPotentiallyDangerousAircraft(Aircraft& aircraft) {
    m_PotentiallyDangerousAircrafts.push_back(aircraft);
}

void Aircraft::removePotentiallyDangerousAircraft(const Aircraft& aircraft) {
    auto it = std::remove(m_PotentiallyDangerousAircrafts.begin(), m_PotentiallyDangerousAircrafts.end(), aircraft);
}

bool operator==(const Aircraft& a1, const Aircraft& a2) {
    return a1.getId() == a2.getId();
}

bool operator!=(const Aircraft& a1, const Aircraft& a2) {
    return !(a1 == a2);
}

//template <typename T>
bool Aircraft::contains(std::vector<std::reference_wrapper<Aircraft>> vec, const Aircraft& elem)
{
    bool result = false;
    for (auto& x : vec)
    {
        if (x.get() == elem)
        {
            result = true;
            break;
        }
    }
    return result;
}

void Aircraft::conflictDetection() {
    // In the model, conflicting aircrafts are added to the list by dangerous radius.
    // Check bounds violation
    for (int i = 0; i < m_PotentiallyDangerousAircrafts.size(); i++) {
        Aircraft& potDangerousAircraft = m_PotentiallyDangerousAircrafts[i];

        // Base variables calculation.
        double delta_X = potDangerousAircraft.x_inMeters() - x_inMeters();
        // Домножение на -1 нужно, так как в формуле ось Y (которая там X) направлена вверх.
        double delta_Y = /*(-1) * */(potDangerousAircraft.y_inMeters() - y_inMeters());
        double delta_Z = potDangerousAircraft.z_inMeters() - z_inMeters();

        // Вопрос про знаки дельт по скоростям: они должны браться со знаками или без?
        double delta_Vx = potDangerousAircraft.getVelocityX() - m_VelocityX;
        double delta_Vy = potDangerousAircraft.getVelocityY() - m_VelocityY;
        double delta_Vz = potDangerousAircraft.getVelocityZ() - m_VelocityZ;

        if (isSeparationStandardsViolated(delta_X, delta_Y, delta_Z)) {
            m_IsInConflict = true;
            potDangerousAircraft.setInConflict(true);
            continue;
        }
        // Derivative calculation. In theory, the derivative sign need to use in visualization...
        double distanceDerivative = getDistanceDerivative(delta_X, delta_Y, delta_Z, delta_Vx, delta_Vy, delta_Vz);
        if (distanceDerivative >= 0) {
            m_IsInConflict = false;
            potDangerousAircraft.setInConflict(false);
        }

        // Check IPSZ intersection
        if (getShifted_IPSZ_Rectangle().intersects(potDangerousAircraft.getShifted_IPSZ_Rectangle())) {
            m_IsZoneIntersects = true;
            potDangerousAircraft.setIsZoneIntersects(true);
        } else {
            m_IsZoneIntersects = false;
            potDangerousAircraft.setIsZoneIntersects(false);
        }

        if (m_Tau_min < 0 && distanceDerivative < 0) {
            // Inverval of minimal distance calculation and vertical and horizontal distance calculation
            double tau_min = (-1) * ((delta_X * delta_Vx + delta_Y * delta_Vy + delta_Z * delta_Vz)) /
                                     (std::pow(delta_Vx, 2) + std::pow(delta_Vy, 2) + std::pow(delta_Vz, 2));
            m_Tau_min = tau_min;

            // Возможно дело в знаках скоростей по осям
            double thisX_tau_min = m_X_inMeters + m_VelocityX * tau_min;
            double thisY_tau_min = m_Y_inMeters + m_VelocityY * tau_min;
            double thisZ_tau_min = m_Z_inMeters + m_VelocityZ * tau_min;

            double x_tau_min = potDangerousAircraft.x_inMeters() + potDangerousAircraft.getVelocityX() * tau_min;
            double y_tau_min = potDangerousAircraft.y_inMeters() + potDangerousAircraft.getVelocityY() * tau_min;
            double z_tau_min = potDangerousAircraft.z_inMeters() + potDangerousAircraft.getVelocityZ() * tau_min;

            double delta_X_tau_min = x_tau_min - thisX_tau_min;
            double delta_Y_tau_min = y_tau_min - thisY_tau_min;
            double delta_Z_tau_min = z_tau_min - thisZ_tau_min;

            // Check bounds violation
            if (isSeparationStandardsViolated(delta_X_tau_min, delta_Y_tau_min, delta_Z_tau_min)) {
                m_IsInConflict = true;
                potDangerousAircraft.setInConflict(true);
            } else {
                m_IsInConflict = false;
                potDangerousAircraft.setInConflict(false);
            }
        }
    }

    // Matrix (?)
}

bool Aircraft::isSeparationStandardsViolated(double delta_X, double delta_Y, double delta_Z) {
    double horDistance = std::sqrt(std::pow(delta_X, 2) + std::pow(delta_Y, 2));
    //double temp = horDistance;
    //qDebug() << "horDistance: " << horDistance;
    return delta_Z <= m_SeparationStandardV && horDistance <= m_SeparationStandardHor;
}

double Aircraft::getDistanceDerivative(double delta_X, double delta_Y, double delta_Z,
                                       double delta_Vx, double delta_Vy, double delta_Vz) {
    double distance = std::sqrt(std::pow(delta_X, 2) + std::pow(delta_Y, 2) + std::pow(delta_Z, 2));
    return ((delta_X * delta_Vx) + (delta_Y * delta_Vy) + (delta_Z * delta_Vz)) / distance;
}

//bool Aircraft::isLinesIntersect(QLine line1, QLine line2) {
//    double v1 = (line2.x2() - line2.x1()) * (line1.y1() - line2.y1()) -
//            (line2.y2() - line2.y1()) * (line1.x1() - line2.x1());
//    double v2 = (line2.x2() - line2.x1()) * (line1.y2() - line2.y1()) -
//            (line2.y2() - line2.y1()) * (line1.x2() - line2.x1());
//    double v3 = (line1.x2() - line1.x1()) * (line2.y1() - line1.y1()) -
//            (line1.y2() - line1.y1()) * (line2.x1() - line1.x1());
//    double v4 = (line1.x2() - line1.x1()) * (line2.y2() - line1.y1()) -
//            (line1.y2() - line1.y1()) * (line2.x2() - line1.x1());

//    return (v1 * v2 < 0) && (v3 * v4 < 0);
//}

//bool Aircraft::isRectanglesIntersect(QRect rect1, QRect rect2) {
//    rect1.i
//}

bool Aircraft::isInConflict() const {
    return m_IsInConflict;
}

void Aircraft::setInConflict(bool value) {
    m_IsInConflict = value;
}

bool Aircraft::isZoneIntersects() const {
    return m_IsZoneIntersects;
}

void Aircraft::setIsZoneIntersects(bool value) {
    m_IsZoneIntersects = value;
}







