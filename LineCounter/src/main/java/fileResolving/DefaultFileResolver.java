package fileResolving;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.nio.file.Files;

public class DefaultFileResolver extends FileResolverBase
{

	@Override
	public String getContent(File file)
	{
		try
		{
			return tryToGetContent(file);
		} catch (IOException e)
		{
			e.printStackTrace();
			return "";
		}
	}

	private String tryToGetContent(File file) throws IOException, UnsupportedEncodingException
	{
		byte[] encoded = Files.readAllBytes(file.toPath());
		return new String(encoded, Charset.defaultCharset());
	}

}
