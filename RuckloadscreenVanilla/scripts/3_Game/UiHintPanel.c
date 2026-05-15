modded class UiHintPanel extends ScriptedWidgetEventHandler
{
	#ifdef DIAG_DEVELOPER
	static int m_ForcedIndex = -1;
	#endif

	protected int 		m_SlideShowDelay = 25000;
	protected string 	m_RootPath = "Gui/layouts/new_ui/hints/in_game_hints.layout";

	protected Widget 				m_RootFrame;
	protected Widget 				m_SpacerFrame;
	protected ButtonWidget 			m_UiLeftButton;
	protected ButtonWidget 			m_UiRightButton;
	protected RichTextWidget		m_UiDescLabel;
	protected TextWidget			m_UiHeadlineLabel;
	protected ImageWidget 			m_UiHintImage;
	protected TextWidget 			m_UiPageingLabel;

	protected ref array<ref RuckusHintPage> m_RuckContent;

	protected int 					m_PageIndex = 0;
	protected DayZGame				m_Game;
	protected bool					m_Initialized;
	protected Widget 				m_ParentWidget;
	protected int					m_PreviousRandomIndex = -1;

	void UiHintPanel(Widget parent_widget)
	{
		DayZGame game = DayZGame.Cast(GetGame());
		m_ParentWidget = parent_widget;
		Init(game);
	}

	void ~UiHintPanel()
	{
		StopSlideShow();
		if (m_RootFrame)
			m_RootFrame.Unlink();
	}

	override void Init(DayZGame game)
	{
		if (m_Initialized)
			return;
		if (!game)
			return;

		m_Initialized = true;
		m_Game = game;

		LoadContentList();

		if (m_RuckContent && m_RuckContent.Count() > 0)
		{
			BuildLayout(m_ParentWidget);
			RandomizePageIndex();
			PopulateLayout();
			StartSlideshow();
		}
		else
		{
			ErrorEx("[Ruckus] Hint panel not created (hints missing/empty).");
		}
	}

	void ReloadFromConfig()
	{
		LoadContentList();

		if (!m_RootFrame)
			return;

		if (m_RuckContent && m_RuckContent.Count() > 0)
		{
			if (m_PageIndex < 0 || m_PageIndex >= m_RuckContent.Count())
				m_PageIndex = 0;

			PopulateLayout();
			RestartSlideShow();
		}
		else
		{
			if (m_UiHeadlineLabel) m_UiHeadlineLabel.SetText("");
			if (m_UiDescLabel)
			{
				m_UiDescLabel.SetText("");
				m_UiDescLabel.Update();
			}
			if (m_UiHintImage) m_UiHintImage.Show(false);
			if (m_UiPageingLabel) m_UiPageingLabel.SetText("");
			StopSlideShow();
		}
	}

	protected void LoadContentList()
	{
		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();
		if (cfg)
			m_RuckContent = cfg.hints;

		if (!m_RuckContent)
			m_RuckContent = new array<ref RuckusHintPage>();

		Print("[Ruckus] UiHintPanel hints loaded: " + m_RuckContent.Count());
		if (m_RuckContent.Count() > 0)
			Print("[Ruckus] First hint: " + m_RuckContent.Get(0).m_Headline);
	}

	protected void BuildLayout(Widget parent_widget)
	{
		m_RootFrame = m_Game.GetWorkspace().CreateWidgets(m_RootPath, parent_widget);

		if (m_RootFrame)
		{
			m_SpacerFrame		= m_RootFrame.FindAnyWidget("GridSpacerWidget1");
			m_UiLeftButton		= ButtonWidget.Cast(m_RootFrame.FindAnyWidget("LeftButton"));
			m_UiRightButton		= ButtonWidget.Cast(m_RootFrame.FindAnyWidget("RightButton"));
			m_UiHeadlineLabel	= TextWidget.Cast(m_RootFrame.FindAnyWidget("HeadlineLabel"));
			m_UiDescLabel		= RichTextWidget.Cast(m_RootFrame.FindAnyWidget("HintDescLabel"));
			m_UiHintImage		= ImageWidget.Cast(m_RootFrame.FindAnyWidget("HintImage"));
			m_UiPageingLabel	= TextWidget.Cast(m_RootFrame.FindAnyWidget("PageInfoLabel"));

			m_RootFrame.SetHandler(this);
		}
	}

	protected void PopulateLayout()
	{
		if (m_RootFrame && m_RuckContent && m_RuckContent.Count() > 0)
		{
			SetHintHeadline();
			SetHintDescription();
			SetHintImage();
			SetHintPaging();
		}
	}

	protected void SetHintHeadline()
	{
		m_UiHeadlineLabel.SetText(m_RuckContent.Get(m_PageIndex).m_Headline);
	}

	protected void SetHintDescription()
	{
		m_UiDescLabel.SetText(m_RuckContent.Get(m_PageIndex).m_Description);
		m_UiDescLabel.Update();
		if (m_SpacerFrame) m_SpacerFrame.Update();
	}

	protected void SetHintImage()
	{
		string image_path = m_RuckContent.Get(m_PageIndex).m_ImagePath;

		if (image_path && image_path != "")
		{
			m_UiHintImage.Show(true);
			m_UiHintImage.LoadImageFile(0, image_path);
		}
		else
		{
			m_UiHintImage.Show(false);
		}
	}

	protected void SetHintPaging()
	{
		if (m_UiPageingLabel)
			m_UiPageingLabel.SetText(string.Format("%1 / %2", m_PageIndex + 1, m_RuckContent.Count()));
	}

	void ShowRandomPage()
	{
		if (!m_RuckContent || m_RuckContent.Count() == 0)
			return;

		RandomizePageIndex();
		PopulateLayout();
	}

	protected void RandomizePageIndex()
	{
		#ifdef DIAG_DEVELOPER
		if (DiagMenu.IsInitialized())
		{
			if (m_ForcedIndex != -1)
			{
				m_PageIndex = Math.Clamp(m_ForcedIndex, 0, m_RuckContent.Count() - 1);
				return;
			}
		}
		#endif

		if (!m_RuckContent || m_RuckContent.Count() == 0)
			return;

		int count = m_RuckContent.Count();

		Math.Randomize(m_Game.GetTime());
		Math.RandomFloat01();

		int next = Math.RandomIntInclusive(0, count - 1);

		if (count > 1)
		{
			while (next == m_PreviousRandomIndex)
				next = Math.RandomIntInclusive(0, count - 1);
		}

		m_PageIndex = next;
		m_PreviousRandomIndex = next;
	}

	protected void ShowNextPage()
	{
		if (!m_RuckContent || m_RuckContent.Count() == 0)
			return;

		if (m_PageIndex < m_RuckContent.Count() - 1)
			m_PageIndex++;
		else
			m_PageIndex = 0;

		PopulateLayout();
	}

	protected void ShowPreviousPage()
	{
		if (!m_RuckContent || m_RuckContent.Count() == 0)
			return;

		if (m_PageIndex == 0)
			m_PageIndex = m_RuckContent.Count() - 1;
		else
			m_PageIndex--;

		PopulateLayout();
	}

	protected void StartSlideshow()
	{
		m_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(SlideshowThread, m_SlideShowDelay);
	}

	protected void SlideshowThread()
	{
		ShowNextPage();
	}

	protected void StopSlideShow()
	{
		m_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(SlideshowThread);
	}

	protected void RestartSlideShow()
	{
		StopSlideShow();
		StartSlideshow();
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (button == MouseState.LEFT)
		{
			switch (w)
			{
				case m_UiLeftButton:
					ShowPreviousPage();
					return true;

				case m_UiRightButton:
					ShowNextPage();
					return true;
			}
		}
		return false;
	}

	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (w == m_RootFrame || w == m_UiLeftButton || w == m_UiRightButton)
		{
			StopSlideShow();
			return true;
		}
		return false;
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (w == m_RootFrame || w == m_UiLeftButton || w == m_UiRightButton)
		{
			RestartSlideShow();
			return true;
		}
		return false;
	}
}

modded class UiHintPanelLoading extends UiHintPanel
{
	override void Init(DayZGame game)
	{
		m_RootPath = "Gui/layouts/new_ui/hints/in_game_hints_load.layout";
		super.Init(game);
	}
}
