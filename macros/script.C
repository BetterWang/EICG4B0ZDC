{

    auto gg = *INPUTGENERATOR::Gun[0];
    gg.set_name("neutron");
    double Eneutron = 100.*MeV;
    double x_ang = 26*mrad;
    gg.set_mom(0., 0., 100.*MeV);
    //gg.set_mom(-Eneutron*x_ang, 0., Eneutron);

    g4->ApplyCommand("/vis/viewer/refresh");
}
