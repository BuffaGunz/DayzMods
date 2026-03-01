class SilentCallBack : RestCallback
{
	override void OnError(int errorCode)
	{
		Print("[ServerStatsDiscord] Webhook ERROR code=" + errorCode.ToString());
	}

	override void OnTimeout()
	{
		Print("[ServerStatsDiscord] Webhook TIMEOUT");
	}

	override void OnSuccess(string data, int dataSize)
	{
		Print("[ServerStatsDiscord] Webhook OK (" + dataSize.ToString() + ")");
	}
};

class DiscordHook
{
	ref map<string, string> m_alias;

	void DiscordHook()
	{
		m_alias = new map<string, string>;
	}

	void SetAlias(string alias, string url)
	{
		m_alias.Set(alias, url);
	}

	private string Escape(string s)
	{
		string bs = "\\";
		string q  = "\"";

		s.Replace(bs, bs + bs);
		s.Replace(q,  bs + q);
		s.Replace("\r", "");
		s.Replace("\n", bs + "n");
		return s;
	}

	bool SendEmbed(string alias, string title, string description)
	{
		if (!m_alias || !m_alias.Contains(alias))
			return false;

		RestApi api = GetRestApi();
		if (!api) api = CreateRestApi();

		RestContext ctx = api.GetRestContext(m_alias.Get(alias));

		ctx.SetHeader("application/json");

		string q = "\"";
		string payload = "{";
		payload = payload + q + "embeds" + q + ":[{";
		payload = payload + q + "title" + q + ":" + q + Escape(title) + q + ",";
		payload = payload + q + "description" + q + ":" + q + Escape(description) + q;
		payload = payload + "}]";
		payload = payload + "}";

		ctx.POST(new SilentCallBack(), "", payload);
		return true;
	}
};

static ref DiscordHook g_discordHook;

static ref DiscordHook GetDiscordHook()
{
	if (!g_discordHook)
		g_discordHook = new DiscordHook();
	return g_discordHook;
}
