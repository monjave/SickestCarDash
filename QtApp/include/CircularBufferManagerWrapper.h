#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include <QDir>
#include <QTimer>

class CircularBufferManagerWrapper : public QObject {
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm WRITE setRPM NOTIFY rpmChanged)
    Q_PROPERTY(double fuel READ fuel WRITE setFuel NOTIFY fuelChanged)
    Q_PROPERTY(double temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(double coolanttemp READ coolanttemp WRITE setCoolanttemp NOTIFY coolanttempChanged)
    Q_PROPERTY(double clock READ clock WRITE setClock NOTIFY clockChanged)
    Q_PROPERTY(double enginetemp READ enginetemp WRITE setEnginetemp NOTIFY enginetempChanged)
    Q_PROPERTY(double oiltemp READ oiltemp WRITE setOilTemp NOTIFY oilTempChanged)

    Q_PROPERTY(double gearshift READ gearshift WRITE setGearShift NOTIFY gearshiftChanged)

    Q_PROPERTY(double seatbelt READ seatbelt WRITE setSeatBelt NOTIFY seatbeltChanged)
    Q_PROPERTY(double highlights READ highlights WRITE setHighlights NOTIFY highlightsChanged)
    Q_PROPERTY(double abs READ abs WRITE setABS NOTIFY absChanged)
    Q_PROPERTY(double enginecheck READ enginecheck WRITE setEngineCheck NOTIFY enginecheckChanged)
    Q_PROPERTY(double parking READ parking WRITE setParking NOTIFY parkingChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr);

    double speed() const;
    double rpm() const;
    double fuel() const;
    double temp() const;
    double coolanttemp() const;
    double clock() const;
    double enginetemp() const;
    double oiltemp() const;

    double gearshift() const;

    double seatbelt() const;
    double highlights() const;
    double abs() const;
    double enginecheck() const;
    double parking() const;


    void setSpeed(double newSpeed);
    void setRPM(double newRPM);
    void setFuel(double newFuel);
    void setTemp(double newTemp);
    void setCoolanttemp(double newCoolanttemp);
    void setClock(double newClock);
    void setEnginetemp(double newEnginetemp);
    void setOilTemp(double newOilTemp);

    void setGearShift(double newGearShift);

    void setSeatBelt(bool newSeatBelt);
    void setHighlights(bool newHighlights);
    void setABS(bool newABS);
    void setEngineCheck(bool newEngineCheck);
    void setParking(bool newParking);

signals:
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void tempChanged();
    void coolanttempChanged();
    void clockChanged();
    void enginetempChanged();
    void oilTempChanged();

    void gearshiftChanged();

    void seatbeltChanged();
    void highlightsChanged();
    void absChanged();
    void enginecheckChanged();
    void parkingChanged();

private:
    double m_speed = 0;
    double m_rpm = 0;
    double m_fuel = 0;
    double m_temp = 0;
    double m_coolanttemp = 0;
    double m_clock = 0;
    double m_enginetemp = 0;
    double m_oiltemp = 0;

    double m_gearshift = 0;

    bool m_seatbelt = 0;
    bool m_highlights = 0;
    bool m_abs = 0;
    bool m_enginecheck = 0;
    bool m_parking = 0;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
