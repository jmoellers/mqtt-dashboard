# include	<QtWidgets>
# include	"grid.h"

int debug = 0;

int
main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char *pname;
    grid *g;

    pname = strrchr(argv[0], '/');
    if (pname != NULL)
	pname++;
    else
	pname = argv[0];

    QSettings settings("Josef Möllers", pname);

    setlocale(LC_NUMERIC, "en_US.UTF8");

    g = new grid(7);

    g->addTile("HAK-T", "/hausanschlusskeller/temperatur", "°C", &settings);
    g->addTile("HAK-F", "/hausanschlusskeller/luftfeuchte", "%", &settings);
    g->addTile("AZ-T", "/arbeitszimmer/temperatur", "°C", &settings);
    g->addTile("AZ-F", "/arbeitszimmer/luftfeuchte", "%", &settings);
    g->addTile("Heizungsraum T", "/heizungsraum/temperatur", "°C", &settings);
    g->addTile("Heizungsraum F", "/heizungsraum/luftfeuchte", "%", &settings);
    g->addTile("Garage T", "/garage/temperatur", "°C", &settings);
    g->addTile("Garage F", "/garage/luftfeuchte", "%", &settings);
    g->addTile("Tkol", "/heizung/solar/Tkol", "°C", &settings);
    g->addTile("Tspu", "/heizung/solar/Tspu", "°C", &settings);
    g->addTile("Pumpe", "/heizung/solar/Pumpe0", "%", &settings);
    g->addTile("Stromverbrauch", "/strom/aktuell", "W", &settings);
    g->addTile("Rolltor", "/garage/rolltor", "0:zu,1:auf", &settings);

    g->show();

    a.exec();
}
