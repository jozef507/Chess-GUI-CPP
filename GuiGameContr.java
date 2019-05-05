
public class GuiGameContr implements Initializable
{
    private Game game;

    /* ********************************************TAH UZIVATELA****************************************/


    /**
     * Funkcia ktorá sa uskutoční ak užívateľ klikne na oblasť kde
     * sa nachádza šachovnica. Povoláva metodu onBoardCLick
     * /pre uhľadnosť/ a vkladá jej argumenty, ktoré sú x-ova
     * suradnica a y-ova suradnica kliku na šachovnicu.
     */
    board.setOnMouseClicked(e -> {
        onBoardClick(e.getX(), e.getY());
    });

    /**
     * Samotná metóda onBoardCLick.
     * @param clickX
     * @param clickY
     */
    private void onBoardClick(double clickX, double clickY)
    {
        System.out.println("["+getGuiFieldOnClickX(clickX)+", "+getGuiFieldOnClickY(clickY)+"]");

        /*
         * Nasledujuce riadky vypocitaju x-ovu a y-ovu poziciu polička (z parametrov funkcie)
         * na ktoré uživateľ klikol. Ak uzivatel klikol mimo platne policko jedna alebo
         * obidve pozicie policka budu nastavene na -1.
         */
        int clickedX = getGuiFieldOnClickX(clickX);
        int clickedY = getGuiFieldOnClickY(clickY);


        if(clickedX != -1 && clickedY != -1)  // kontrola či uzivatel klikol na platne políčko
        {
            /**
             * Nasledujúca podmienka najprv overí či nastavenie ťahu (funckia game.setPlayerMovement s parametrami
             * x-ovej a y-ovej pozicie kliknuteho polička) prebehla úspešne (true), ak nie nič sa neudeje.
             *
             * Nasledne podmienka overuje či by bol ťah (movement) kompletne nastavený (funkcia game.isMovementCompletlySet)
             * , ktorá vrati true len v prípade že už bolo nastavené aj cieľove políčko šachovnice (kám sa ma figurka pohnuť)
             * , to znamená že uživateľ klikol už na druhé platne políčko to znamená že aj na štartovacie políčko aj na cieľové
             * poličko. Ak bolo nastavene zatiaľ (uzivateľ klikol) iba štartovacie poličko (uzivateľ klikol) tato metoda
             * vrati false a teda nedostane podmienka povolenie previesť ťah prostrednictvom vnorene volanej funkcie
             * performMovement()
             */
            if(game.setPlayerMovement(clickedX, clickedY) && game.isMovementCompletlySet())
            {
                /**
                 * povolana funckia performMovement ktorá v logike (game) prevedie daný ťah.
                 * Vracia hodnotu boolen - true, ak bol ťah úspešne prevedený
                 *                       - false, ak ťah nebol vyznamovo správny, napríklad ak veža bola presunuta
                 *                         na poličko kam ísť nemôže.
                 */
                boolean flagPerformMovement = game.performPlayerMovement();

                /**
                 * Podmineka overuje či bol ťah úspešne prevedený.
                 *
                 * Ak áno(true) vojde do prvej vetvy kde sa prevedie tento ťah aj graficky.
                 * Ak nie(false) vojde do vetv else kde sa vynuluje(uzatvorí) ťah  hráča.
                 */
                if(flagPerformMovement)
                {
                    //metoda guiMoveFigureImage, iba graficky presunie figurku na spravne miesto
                    guiMoveFigureImage(game.getImageOfMovFigure(), game.getGoalField().getColPos(), game.getGoalField().getRowPos());
                    board.setDisable(true);


                    if(game.isRemovingFigure())
                        game.getImageOfGoalFieldFigure().setOpacity(0.35);


                    Timeline timeline;

                    /**
                     * Podmienka pomocou funkcie game.getIsChangingFigure() overuje či sa pri prevedeni ťahu (v logike)
                     * ocitol pešiak (ak dana figurka bola pešiak) na políčku kde je potrebná vymena tohto pešiaka
                     * za novú figúrku. Vracia true ak áno.
                     *
                     * Ak áno vojde do prvej vetvy a pomocou funkcie,
                     * showChangingFigures() sa graficky na šachovnici objavia tlačítka figúrok, za ktoré môže užívateľ
                     * tohto pešiaka vymeniť. V tomto prípade nie je ešte možné ťah (v logike) vynulovať, to sa spraví
                     * až po tom čo si užívateľ vyberie nahradnu figurku.
                     *
                     * Ak nie vojde do vetvy else, kde sa na konci pomocou funkcie this.closePlayerMovent vynuluje(zatvorí)
                     * ťah užívateľa aj grafiky aj v logike. (okomentovane pri definicii metódy)
                     */
                    if(game.getIsChangingFigure())
                    {
                        timeline = new Timeline(new KeyFrame(Duration.millis((100*this.fieldDiff)+10), ev -> {

                            /**
                             * podmienka pomocou funkcie game.isRemovingFigure() overuje či pri prevedeni ťahu (v logike)
                             * sa odstraňovala figurka. Ak áno funkcia vrati true a v tele podmienky sa graficky odstrani
                             * vyhodena figurka zo šachovnice.
                             */
                            if(game.isRemovingFigure())
                                game.getImageOfGoalFieldFigure().setVisible(false);

                            board.setDisable(false);
                            showChangingFigures();
                            //timeline.cancel();
                        }));
                    }
                    else
                    {
                        timeline = new Timeline(new KeyFrame(Duration.millis((100*this.fieldDiff)+10), ev -> {

                            /**
                             * podmienka pomocou funkcie game.isRemovingFigure() overuje či pri prevedeni ťahu (v logike)
                             * sa odstraňovala figurka. Ak áno funkcia vrati true a v tele podmienky sa graficky odstrani
                             * vyhodena figurka zo šachovnice.
                             */
                            if(game.isRemovingFigure())
                                game.getImageOfGoalFieldFigure().setVisible(false);

                            board.setDisable(false);
                            this.closePlayerMovement();
                        }));
                    }
                    timeline.play();
                }
                else
                {
                    /**
                     * Funkcia pre vynulovanie ťahu v logike.
                     */
                    game.nullMovementManager();
                }
            }
        }
    }


    /**
     * Nasledujúcich 8 funkcii sa vykona ak uživatel klikne na tlačitko
     * s figurkou ktorú môže zameniť za pešiaka.
     * Dôležita pre logiku je hneĎ prvá funkcia this.new[nazov_figurky][farba_figurky]()
     * ktorá oznámi logike ktorú figúrku má vytvoriť. Logika si sama z nastaveneho
     * ťahu určí kam sa figurka položí (v logike)
     *
     * Na konci funkcie sa povola funkcia this.closePlayerMovement() ktorá zatvorí(vynuluje)
     * ťah hráča tak ako v logike tak aj graficky.
     */
    buttonRookWhite.setOnMouseClicked(e -> {
        this.newRookWhite();
        hideChangingFigures(); // ukryje tlačitka s vyberom novej figurky.
        this.closePlayerMovement();
    });


    buttonKnightWhite.setOnMouseClicked(e -> {
        this.newKnightWhite();
        hideChangingFigures();
        this.closePlayerMovement();
    });


    buttonBishopWhite.setOnMouseClicked(e -> {
        this.newBishopWhite();
        hideChangingFigures();
        this.closePlayerMovement();
    });

    buttonQueenWhite.setOnMouseClicked(e -> {
        this.newQueenWhite();
        hideChangingFigures();
        this.closePlayerMovement();
    });

    buttonRookBlack.setOnMouseClicked(e -> {
        this.newRookBlack();
        hideChangingFigures();
        this.closePlayerMovement();
    });

    buttonKnightBlack.setOnMouseClicked(e -> {
        this.newKnightBlack();
        hideChangingFigures();
        this.closePlayerMovement();

    });

    buttonBishopBlack.setOnMouseClicked(e -> {
        this.newBishopBlack();
        hideChangingFigures();
        this.closePlayerMovement();
    });

    buttonQueenBlack.setOnMouseClicked(e -> {
        this.newQueenBlack();
        hideChangingFigures();
        this.closePlayerMovement();

    });


    /**
     * Nasledujucich 8 funkcii vytvorí danu figurku podľa potreby.
     */
    private void newRookWhite()
    {
        //gui - vytvorenie noveho obrazka pre figurku
        ImageView imageView = new ImageView("sample/images/rook_white.png");
        //gui - vloženie obrazka na šachovnicu
        this.newFigureImageOnBoard(imageView);

        /**
         * vytvorenie novej figurky v logike, kde sa vklada obrazok tejto figurky z guika
         * a takisto id (typ) figurky ktorá sa ma v logike vytvoriť.
         */
        game.createNewFigure(imageView, 4);
        this.whiteFiguresImages.add(imageView);
    }

    private void newKnightWhite()
    {
        ImageView imageView = new ImageView("sample/images/knight_white.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 3);
        this.whiteFiguresImages.add(imageView);
    }

    private void newBishopWhite()
    {
        ImageView imageView = new ImageView("sample/images/bishop_white.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 2);
        this.whiteFiguresImages.add(imageView);
    }

    private void newQueenWhite()
    {
        ImageView imageView = new ImageView("sample/images/queen_white.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 1);
        this.witeFiguresImages.add(imageView);
    }

    private void newRookBlack()
    {
        ImageView imageView = new ImageView("sample/images/rook_dark.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 4);
        this.whiteFiguresImages.add(imageView);
    }

    private void newKnightBlack()
    {
        ImageView imageView = new ImageView("sample/images/knight_dark.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 3);
        this.whiteFiguresImages.add(imageView);
    }

    private void newBishopBlack()
    {
        ImageView imageView = new ImageView("sample/images/bishop_dark.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 2);
        this.whiteFiguresImages.add(imageView);
    }

    private void newQueenBlack()
    {
        ImageView imageView = new ImageView("sample/images/queen_dark.png");
        this.newFigureImageOnBoard(imageView);
        game.createNewFigure(imageView, 1);
        this.whiteFiguresImages.add(imageView);
    }


    /**
     * Funkcia ktorá ukončuje/vynuluje/zatvorí ťah hráča v logike aj grafike;
     */
    private void closePlayerMovement()
    {
        /**
         * táto funkcia vytvorí ťah v zapise šachovej partie a vymaže všetky nasledujuce
         * už nepotrebné zapisy ťahov v šachovej notacii (v prípade že sa prehravanie šachovej partie
         * ukončí niekde v strede a potom uživateľ spraví vlastný ťah.
         */
        game.addPlayerNotationMovement();

        /**
         * setTextArea graficky nastaví textove pole kde sa zobrazuje šachova notacia
         * do prveho parametru sa vklada celá šachova notacia(z logiky - game.getGameNotation)
         * aktualna pre tento ťah. Notacia nie je vratena jednym dlhym stringom ale vectorom
         * stringov kde jedna položka predstavuje jeden riadok notacie.
         * Druhy parameter int-ove poradie riadka ktoré ma byť v grafike v notacii vyznačnený
         * Pozor nezabudnuť na to +1;
         */
        setTextArea(game.getGameNotation(), game.getIndexOfGameNotation()+1);

        /**
         * V prípade že ide o kratku formu notacie tak tato funkcia doplni dôležite informacie
         * o štartovacom poličku do tejto notacie
         */
        game.completeNotationMovement();

        /**
         * Funkcia pre vynulovanie ťahu v logike.
         */
        game.nullMovementManager();

        /**
         * Funkcia ktorá v logike zmení hráča ktorý je na ťahu.
         */
        game.changePlayer();
        guiChangePlayer();
        this.buttonCheckment();
    }














/* *******************************************TAH OVLADANY NOTACIOU**************************************************/

    /**
     * Funkcia volána pri kliknutí na tlačítko Redo (krok dopredu v šachovej partii) a takisto
     * na tlačítko Play ktorá prehráva šachovu partiu.  V prípade že je povolana na zaklade
     * tlačitka play tak sa nastavuje bool recursive na true čím sa bude postupne
     * automaticky vykonavať. Takisto sa nastaví delay pre delay medzi jednotlivými ťahmi.
     * @param recursive
     * @param delay
     */
    private void playbackMovement(boolean recursive, double delay)
    {
        /**
         * Prostrednictvom game.setPlaybackMovent sa v logike ťah na zadklade ťahu zapísanom v notácii
         * (nastavuje sa hned aj štartovacie poličko aj cieľove. V prípade úspešneho nastavenia sa
         * vrati true a vojde sa do vetvy podmientky.
         */
        if(game.setPlaybackMovement())
        {

            /**
             * Prostrednictvom game.performPlaybackMovement sa prevedie v logike už nastavený ťah
             * v prípade uspechu vracia true a vojde sa do vetvy overovacej podmienky.
             */
            boolean flagPerformMovement = game.performPlaybackMovement();
            if(flagPerformMovement)
            {

                //grafické presunutie figurky
                guiMoveFigureImage(game.getImageOfMovFigure(), game.getGoalField().getColPos(), game.getGoalField().getRowPos());
                board.setDisable(true);
                redoButton.setDisable(true);
                undoButton.setDisable(true);
                restartButton.setDisable(true);
                saveButton.setDisable(true);

                //kontrola či bola vyhodena figurka
                if(game.isRemovingFigure())
                    game.getImageOfGoalFieldFigure().setOpacity(0.35);


                Timeline timeline;
                timeline = new Timeline(new KeyFrame(Duration.millis((100*this.fieldDiff)+delay), ev -> {

                    //kontrola či bola vyhodena figurka
                    if(game.isRemovingFigure())
                        game.getImageOfGoalFieldFigure().setVisible(false);
                    board.setDisable(false);
                    redoButton.setDisable(false);
                    undoButton.setDisable(false);
                    restartButton.setDisable(false);
                    saveButton.setDisable(false);

                    /**
                     * Kontrola či je potreba zameniť pešiaka za novu figurku
                     * Ak áno (true) tak sa z notacie pomocou game.getCHangingFigureID()
                     * zisti ID figurky ktorá ma nahradiť pešiaka.
                     */
                    if(game.getIsChangingFigure())
                    {
                        int id = this.game.getChangingFigureID();

                        /**
                         * Kontrola id (typu) figurky a farby figurky ktorá
                         * má vymeniť pešiaka, podľa toho sa volá príslušná metoda
                         * ktorá vytvorí danú figurku.
                         */
                        if(id==4 && this.game.isWhiteOnTheMove())
                            this.newRookWhite();
                        else if(id==4 && !this.game.isWhiteOnTheMove())
                            this.newRookBlack();
                        else if(id==3 && this.game.isWhiteOnTheMove())
                            this.newBishopWhite();
                        else if(id==3 && !this.game.isWhiteOnTheMove())
                            this.newBishopBlack();
                        else if(id==2 && this.game.isWhiteOnTheMove())
                            this.newKnightWhite();
                        else if(id==2 && !this.game.isWhiteOnTheMove())
                            this.newKnightBlack();
                        else if(id==1 && this.game.isWhiteOnTheMove())
                            this.newQueenWhite();
                        else if(id==1 && !this.game.isWhiteOnTheMove())
                            this.newQueenBlack();
                    }

                    /**
                     * inkrementuje index ťahu notácie ktorý sa prave vykonával
                     */
                    this.game.incrementIndexOfNotationLines();

                    /**
                     * nastavenie notacie v grafike (rovnako ako pri ťahu užívateľa
                     */
                    setTextArea(game.getGameNotation(), game.getIndexOfGameNotation()+1);

                    /**
                     * uzatvorí/vynuluje ťah ovladaný notáciou (okomentovany nižšie)
                     */
                    this.closePlaybackMovement();

                    /**
                     * rekurzivne volanie pri spustení tlačítka play
                     */
                    if(recursive && this.recur)
                        playbackMovement(recursive, delay);
                }));
                timeline.play();
            }
            else
            {
                /**
                 * V prípade neuspechu prevedenia ťahu v logike sa vynuluje v logike tento ťah.
                 */
                game.nullMovementManager();
            }
        }
    }


    /**
     * Funkcia ktorá ukončuje/vynuluje/zatvorí ťah organizovaný notáciou
     */
    private void closePlaybackMovement()
    {
        /**
         * Skompletovanie notacie pri kratkej forme notacie.
         */
        game.completeNotationMovement();

        /**
         * vynulovanie ťahu v logike
         */
        game.nullMovementManager();

        /**
         * zmena hráča v logike
         */
        game.changePlayer();

        //gui -> graficke vyznačenie zmeny hráča a kontrola pre odstavenie tlačitok vprípade potreby
        guiChangePlayer();
        this.buttonCheckment();
    }












/* *******************************************TAH SPAT(BACK) OVLADANY NOTACIOU*****************************************/
    /**
     * Funkcia volána pri kliknutí na tlačítko Undo (krok vzad v šachovej partii) a takisto
     * na tlačítko Reset ktoré resetuje partiu na začiatok.  V prípade že je povolana na zaklade
     * tlačitka reset tak sa nastavuje bool recursive na true čím sa bude postupne
     * automaticky vykonavať.
     * @param recur
     */
    private void playbackUndoMovement(boolean recur)
    {
        /**
         * Nastaví s ťah v zad podľa notácie v samotnej logíke a v prípade úspechu sa prejde
         * vykonavanie -> performPlabyckUndoMovement
         */
        if(game.setPlaybackUndoMovement())
        {
            /**
             * v prípade uspechu performMovement (true) sa vojde do tela podmienky.
             */
            boolean flagPerformMovement = game.performPlaybackUndoMovement();
            if(flagPerformMovement)
            {
                //kontorla či došlo k zamene figurky pre potreby gui
                if(game.getMovementManager().getIsChangingFigure())
                {
                    this.board.getChildren().remove(game.getMovementManager().getChangingFigure().getImage());
                    if(game.getMovementManager().getChangingFigure().isWhite())
                        this.whiteFiguresImages.remove(game.getMovementManager().getChangingFigure().getImage());
                    else
                        this.blackFiguresImages.remove(game.getMovementManager().getChangingFigure().getImage());
                    game.getMovementManager().getMovementFigure().getImage().setVisible(true);
                }

                //gui- nastavenie pozicie obrazka figurky
                ImageView image = game.getMovementManager().getMovementFigure().getImage();
                int fromFieldX = getGuiFieldOfImageX(image.getLayoutX());
                int fromFieldY = getGuiFieldOfImageY(image.getLayoutY());
                double toY = getGuiPositionOfImageY(game.getMovementManager().getStartField().getRowPos()) - getGuiPositionOfImageY(fromFieldY);
                double toX = getGuiPositionOfImageX(game.getMovementManager().getStartField().getColPos()) - getGuiPositionOfImageX(fromFieldX);
                image.setTranslateX(toX);
                image.setTranslateY(toY);

                //kontola či bola vyhodena v tomto ťahu figurka, pre potreby gui
                if(game.getMovementManager().getIsRemovingFigure())
                {
                    game.getMovementManager().getGoalFieldFigure().getImage().setVisible(true);
                }

                /**
                 * Dekrementacia indexu pre aktualny ťah notácie
                 */
                game.decrementIndexOfNotationLines();
                /**
                 * zobrazenie notacie v gui
                 */
                setTextArea(game.getGameNotation(), game.getIndexOfGameNotation()+1);
                /**
                 * vynulovanie ťahu v logike
                 */
                game.nullMovementManager();
                //kontola tlačitok a ich odstavenie v prípade potreby
                this.buttonCheckment();
                //recurzivne volanie metody v prípade tlačitka reset
                if(this.backRecur && recur)
                    playbackUndoMovement(recur);

            }
            else
            {
                /**
                 * vynulovanie ťahu v logike po neuspešnom prevedeni ťahu (if)
                 */
                game.nullMovementManager();
            }
        }
    }



















}




